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
			ERR("(Window Title: \"{0}\") Failed to create GLFW window.", title);
			glfwTerminate();
			return;
		}
		INFO("(Window Title: \"{0}\") Successful to create GLFW window.", title);

		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, this);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			ERR("(Window Title: \"{0}\") Failed to initialize GLAD.", title);
			return;
		}

		SetupWindowEvent();
	}

	Window::~Window()
	{
		glfwDestroyWindow(glfwWindow);
	}

	void Window::Update()
	{
		if (isClosed)
			return;

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}

	void Window::Close()
	{
		if (isClosed)
		{
			WARN("(Window Title: \"{0}\") Window is already closed.", title);
			return;
		}

		OnWindowClosed.Publish(this);
		isClosed = true;
		glfwTerminate();

		INFO("(Window Title: \"{0}\") Window successfully close.", title);
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
				currentWindow->OnWindowFocused.Publish(currentWindow);
				INFO("(Window Title: \"{0}\") Window got focus.", currentWindow->GetTitle());
			}
			else
			{
				currentWindow->OnWindowLostFocus.Publish(currentWindow);
				INFO("(Window Title: \"{0}\") Window lost focus.", currentWindow->GetTitle());
			}
		});

		glfwSetKeyCallback(this->glfwWindow, [](GLFWwindow* win, int key, int scancode, int action, int mods)
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			if (action == GLFW_PRESS)
			{
				currentWindow->OnKeyPressed.Publish(currentWindow, key);
				INFO("(Window Title: \"{0}\") Key pressed: {1}.", currentWindow->GetTitle(), key);
			}
			else if (action == GLFW_REPEAT)
			{
				currentWindow->OnKeyHold.Publish(currentWindow, key);
				INFO("(Window Title: \"{0}\") Key hold: {1}.", currentWindow->GetTitle(), key);
			}
			else if (action == GLFW_RELEASE)
			{
				currentWindow->OnKeyReleased.Publish(currentWindow, key);
				INFO("(Window Title: \"{0}\") Key released: {1}.", currentWindow->GetTitle(), key);
			}
		});
	}
}
