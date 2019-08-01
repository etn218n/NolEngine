#pragma once

#include "NolAPI.h"

namespace Nol
{
	enum class EventType
	{
		None,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = (1 << 0),
		EventCategoryInput		 = (1 << 1),
		EventCategoryKeyboard	 = (1 << 2),
		EventCategoryMouse		 = (1 << 3),
		EventCategoryMouseButton = (1 << 4),
	};

	class NOL_API Event
	{
	private:
		bool _isHandled;

	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags()   const = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
}
