#include "PCH.h"
#include "Window.h"

namespace Nol
{
	#pragma region <Initialization>
	/*-------------------------------------------------------------------------------------------------------*/
	Window::Window(const std::string& title, unsigned int width, unsigned int height, bool isVsyncEnabled, GLFWwindow* sharedContextWindow) :
		title(title), width(width), height(height), isVsyncEnabled(isVsyncEnabled), isClosed(false)
	{
		if (sharedContextWindow == nullptr)
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}

		glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, sharedContextWindow);

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

		glfwMakeContextCurrent(NULL);

		SetVsync(isVsyncEnabled);
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
				currentWindow->OnFocused.Publish(currentWindow);
				INFO("(Window \"{0}\") Window gained focus.", currentWindow->Title());
			}
			else
			{
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
					Input::holdKeys[button].first = KeyState::Pressed;
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

			INFO("(Window \"{0}\") Window moved to ({1}, {2}).", currentWindow->Title(), x, y);
		});
	}
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion

	#pragma region <Core Functionalities>
	/*-------------------------------------------------------------------------------------------------------*/
	void Window::Update()
	{
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
		glfwMakeContextCurrent(glfwWindow);

		if (val == true)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		isVsyncEnabled = val;

		glfwMakeContextCurrent(NULL);
	}	
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion
}
