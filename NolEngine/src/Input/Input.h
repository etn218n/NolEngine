#pragma once

#include "NolAPI.h"

#include "Input/Keycode.h"

#include "Core/Window.h"
#include "Core/Log.h"

namespace Nol
{
	class Input
	{
	friend class Window;

	public:
		NOL_API static bool IfKeyPressed(Keycode keycode);
		NOL_API static bool IfKeyReleased(Keycode keycode);

		NOL_API static bool IfMousePressed(Keycode keycode);
		NOL_API static bool IfMouseReleased(Keycode keycode);

	private:
		static Window* activeWindow;
	};
}

