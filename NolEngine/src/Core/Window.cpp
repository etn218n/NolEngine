#include "PCH.h"
#include "Window.h"

namespace Nol
{
	Window::Window(const std::string& title, unsigned int width, unsigned int height, bool isVsyncEnable) :
		title(title), width(width), height(height), isVsyncEnabled(isVsyncEnable), isClosed(false)
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

		glfwMakeContextCurrent(NULL);
	}

	Window::~Window()
	{
	}

	void Window::Update()
	{
		if (isClosed)
		{
			WARN("(Window \"{0}\") Trying to update a closed window.", title);
			return;
		}

		glfwMakeContextCurrent(this->glfwWindow);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
		if (val == true)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		isVsyncEnabled = val;
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
				currentWindow->OnFocused.Publish(currentWindow);
				INFO("(Window \"{0}\") Window gained focus.", currentWindow->GetTitle());
			}
			else
			{
				Input::activeWindow = nullptr;
				currentWindow->OnLostFocus.Publish(currentWindow);
				INFO("(Window \"{0}\") Window lost focus.", currentWindow->GetTitle());
			}
		});

		glfwSetCursorPosCallback(this->glfwWindow, [](GLFWwindow* win, double x, double y)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			currentWindow->OnMouseMoved.Publish(currentWindow, x, y);
		});

		glfwSetMouseButtonCallback(this->glfwWindow, [](GLFWwindow* win, int button, int action, int mods)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			switch (action)
			{
				case GLFW_PRESS: {
					currentWindow->OnMousePressed.Publish(currentWindow, (Keycode)button);
					break;
				}
				case GLFW_RELEASE: {
					currentWindow->OnMouseReleased.Publish(currentWindow, (Keycode)button);
					break;
				}
				default: {
					WARN("(Window \"{0}\") Unkown mouse button action.", currentWindow->GetTitle());
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
					break;
				}
				case GLFW_REPEAT: {
					currentWindow->OnKeyHold.Publish(currentWindow, (Keycode)key);
					break;
				}
				case GLFW_RELEASE: {
					currentWindow->OnKeyReleased.Publish(currentWindow, (Keycode)key);
					break;
				}
				default: {
					WARN("(Window \"{0}\") Unkown key action.", currentWindow->GetTitle());
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
