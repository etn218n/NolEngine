#pragma once

#include "NolAPI.h"
#include <string>
#include <functional>

namespace Nol
{
	class NOL_API WindowProperty
	{
	private:
		std::string  title;
		unsigned int width;
		unsigned int height;

	public:
		WindowProperty(const std::string& title, unsigned int width = 800, unsigned int height = 600) :
			title(title), width(width), height(height) {}

		inline const std::string& GetTitle()  const { return title;  }
		inline const unsigned int GetWidth()  const { return width;  }
		inline const unsigned int GetHeight() const { return height; }
	};

	class NOL_API Window
	{
	public:
		//using EventCallbackFn = std::function<void(Event&)>;
		Window();
		virtual ~Window();
	};
}


