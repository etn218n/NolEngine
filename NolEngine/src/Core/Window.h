#pragma once

#include "NolAPI.h"
#include <string>
#include <functional>

namespace Nol
{
	class WindowProperty
	{
	private:
		std::string  _title;
		unsigned int _width;
		unsigned int _height;

	public:
		WindowProperty(const std::string& title, unsigned int width = 800, unsigned int height = 600) :
			_title(title), _width(width), _height(height) {}

		inline const std::string& GetTitle() const { return _title; }

		inline const unsigned int GetWidth()  const { return _width;  }
		inline const unsigned int GetHeight() const { return _height; }
	};

	class NOL_API Window
	{
	public:
		//using EventCallbackFn = std::function<void(Event&)>;
		Window();
		virtual ~Window();
	};
}


