#pragma once

#include "NolAPI.h"
#include "PCH.h"

#include "Event/Observable.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Nol
{
	class NOL_API Window
	{
	public:
		Observable<Window*> OnWindowClosed;

	private:
		GLFWwindow*  glfwWindow;
		std::string  title;
		unsigned int width;
		unsigned int height;
		bool isVsyncEnabled;
		bool isClosed;

	public:
		Window(const std::string& title = "Untitled", unsigned int width = 800, unsigned int height = 600, bool isVsyncEnable = false);
		Window(const Window& other) = delete;
		virtual ~Window();

		void Update();
		void Close();
		void SetVsync(bool val);

		inline const std::string& GetTitle()  const { return title;			 }
		inline const unsigned int GetWidth()  const { return width;			 }
		inline const unsigned int GetHeight() const { return height;		 }
		inline const bool IsVsyncEnabled()    const { return isVsyncEnabled; }
		inline const bool IsClosed()		  const { return isClosed;		 }

	private:
		void SetupWindowEvent();
	};
}


