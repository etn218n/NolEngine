#include "PCH.h"
#include "Input.h"

namespace Nol
{
	Window* Input::activeWindow = nullptr;

	bool Input::IfKeyPressed(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		int state = glfwGetKey(activeWindow->GetGLFWWindow(), (int)keycode);

		return state == GLFW_PRESS;
	}

	bool Input::IfKeyReleased(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		int state = glfwGetKey(activeWindow->GetGLFWWindow(), (int)keycode);

		return state == GLFW_RELEASE;
	}

	bool Input::IfMousePressed(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		int state = glfwGetMouseButton(activeWindow->GetGLFWWindow(), (int)keycode);

		return state == GLFW_PRESS;
	}

	bool Input::IfMouseReleased(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		int state = glfwGetMouseButton(activeWindow->GetGLFWWindow(), (int)keycode);

		return state == GLFW_RELEASE;
	}
}
