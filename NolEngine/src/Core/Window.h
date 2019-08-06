#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Event/Observable.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Nol
{
	class Window
	{
	public:
		Observable<Window*> OnWindowClosed;
		Observable<Window*> OnWindowFocused;
		Observable<Window*> OnWindowLostFocus;

	private:
		GLFWwindow*  glfwWindow;
		std::string  title;
		unsigned int width;
		unsigned int height;
		bool isVsyncEnabled;
		bool isClosed;

	public:
		NOL_API Window(const std::string& title = "Untitled", unsigned int width = 800, unsigned int height = 600, bool isVsyncEnable = false);
		NOL_API Window(const Window& other) = delete;
		NOL_API virtual ~Window();

		NOL_API void Update();
		NOL_API void Close();
		NOL_API void SetVsync(bool val);

		NOL_API inline const std::string& GetTitle()  const { return title;			 }
		NOL_API inline const unsigned int GetWidth()  const { return width;			 }
		NOL_API inline const unsigned int GetHeight() const { return height;		 }
		NOL_API inline const bool IsVsyncEnabled()    const { return isVsyncEnabled; }
		NOL_API inline const bool IsClosed()		  const { return isClosed;		 }

	private:
		void SetupWindowEvent();
	};
}


