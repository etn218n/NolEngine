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
			ERR("Failed to create GLFW window.(Window Title: \"{0}\")", title);
			glfwTerminate();
			return;
		}
		INFO("Successful to create GLFW window.(Window Title: \"{0}\")", title);

		glfwMakeContextCurrent(glfwWindow);
		glfwSetWindowUserPointer(glfwWindow, this);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			ERR("Failed to initialize GLAD.");
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
			WARN("GLFW window is already closed.(Window Title: \"{0}\")", title);
			return;
		}

		OnWindowClosed.Publish(this);
		isClosed = true;
		glfwTerminate();

		INFO("Successful to close GLFW window.(Window Title: \"{0}\")", title);
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
		glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* win) 
		{
			Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(win));

			currentWindow->Close();
		});
	}
}
