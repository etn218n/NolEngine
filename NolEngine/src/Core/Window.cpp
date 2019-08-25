#include "PCH.h"
#include "Window.h"

namespace Nol
{
	Window::Window(const std::string& title, unsigned int width, unsigned int height, bool isVsyncEnabled) :
		title(title), width(width), height(height), isVsyncEnabled(isVsyncEnabled), isClosed(false)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (glfwWindow == nullptr)
		{
			ERR("(Window \"{0}\") Failed to create GLFW window.", title);
			glfwTerminate();
			return;
		}
		INFO("(Window \"{0}\") Successful to create GLFW window.", title);

		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, this);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			ERR("(Window \"{0}\") Failed to initialize GLAD.", title);
			return;
		}

		SetupWindowEvent();

		SetVsync(isVsyncEnabled);

		// Black is default background color
		SetBackgroundColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		Input::activeWindow = this;

		glfwMakeContextCurrent(NULL);
	}

	void Window::Update()
	{
		if (isClosed)
		{
			WARN("(Window \"{0}\") Trying to update a closed window.", title);
			return;
		}

		double currentTime = glfwGetTime();

		glfwMakeContextCurrent(this->glfwWindow);

		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// For testing purpose
		OnUpdate.Publish(this);

		if (Input::activeWindow == this)
			Input::UpdateInputState(currentTime);

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}

	void Window::Close()
	{
		if (isClosed)
		{
			WARN("(Window \"{0}\") Window is already closed.", title);
			return;
		}

		OnClosed.Publish(this);
		isClosed = true;
		glfwDestroyWindow(glfwWindow);

		INFO("(Window \"{0}\") Window successfully close.", title);
	}

	void Window::SetVsync(bool val)
	{
		glfwMakeContextCurrent(this->glfwWindow);

		if (val == true)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		isVsyncEnabled = val;

		glfwMakeContextCurrent(NULL);
	}

	void Window::SetupWindowEvent()
	{
		glfwSetWindowCloseCallback(this->glfwWindow, [](GLFWwindow* win) 
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			currentWindow->Close();
		});

		glfwSetWindowFocusCallback(this->glfwWindow, [](GLFWwindow* win, int isFocused)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			if (isFocused)
			{
				Input::activeWindow = currentWindow;
				Input::UpdateInputState(glfwGetTime());
				currentWindow->OnFocused.Publish(currentWindow);
				INFO("(Window \"{0}\") Window gained focus.", currentWindow->Title());
			}
			else
			{
				Input::activeWindow = nullptr;
				WARN("Input::activeWindow is NULL.");
				currentWindow->OnLostFocus.Publish(currentWindow);
				INFO("(Window \"{0}\") Window lost focus.", currentWindow->Title());
			}
		});

		glfwSetCursorPosCallback(this->glfwWindow, [](GLFWwindow* win, double x, double y)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			currentWindow->OnMouseMoved.Publish(currentWindow, x, y);

			Input::mousePosition.x = x;
			Input::mousePosition.y = y;
		});

		// TODO: decoupled setting keystate by making Input listen to window input events
		glfwSetMouseButtonCallback(this->glfwWindow, [](GLFWwindow* win, int button, int action, int mods)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			switch (action)
			{
				case GLFW_PRESS: {
					currentWindow->OnMousePressed.Publish(currentWindow, (Keycode)button);
					Input::stateArray[button] = KeyState::Pressed;
					Input::indexOfUpdatedKeys.push_back(button);
					Input::holdKeys[button].first  = KeyState::Pressed;
					Input::holdKeys[button].second = glfwGetTime();
					Input::OnMousePressed.Publish((Keycode)button);
					break;
				}
				case GLFW_RELEASE: {
					currentWindow->OnMouseReleased.Publish(currentWindow, (Keycode)button);
					Input::stateArray[button] = KeyState::Released;
					Input::indexOfUpdatedKeys.push_back(button);
					Input::holdKeys[button].first = KeyState::Released;
					Input::OnMouseReleased.Publish((Keycode)button);
					break;
				}
				default: {
					WARN("(Window \"{0}\") Unkown mouse button action.", currentWindow->Title());
					break;
				}
			}
		});

		glfwSetKeyCallback(this->glfwWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			switch (action)
			{
				case GLFW_PRESS: {
					currentWindow->OnKeyPressed.Publish(currentWindow, (Keycode)key);
					Input::stateArray[key] = KeyState::Pressed;
					Input::indexOfUpdatedKeys.push_back(key);
					Input::OnKeyPressed.Publish((Keycode)key);
					break;
				}
				case GLFW_REPEAT: {
					currentWindow->OnKeyHold.Publish(currentWindow, (Keycode)key);
					Input::stateArray[key] = KeyState::Hold;
					Input::OnKeyHold.Publish((Keycode)key);
					break;
				}
				case GLFW_RELEASE: {
					currentWindow->OnKeyReleased.Publish(currentWindow, (Keycode)key);
					Input::stateArray[key] = KeyState::Released;
					Input::indexOfUpdatedKeys.push_back(key);
					Input::OnKeyReleased.Publish((Keycode)key);
					break;
				}
				default: {
					WARN("(Window \"{0}\") Unkown key action.", currentWindow->Title());
					break;
				}
			}
		});

		glfwSetWindowPosCallback(this->glfwWindow, [](GLFWwindow* win, int x, int y)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			currentWindow->OnPositionChanged.Publish(currentWindow, x, y);
		});
	}
}
