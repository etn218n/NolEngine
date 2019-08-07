#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Input/Keycode.h"

#include "Core/Window.h"
#include "Core/Log.h"

#include "Event/Observable.h"

namespace Nol
{
	enum KeyState { Unpressed, Pressed, Hold, Released };

	class Input
	{
	friend class Window;

	public:
		NOL_API static Observable<Keycode> OnKeyPressed;
		NOL_API static Observable<Keycode> OnKeyHold;
		NOL_API static Observable<Keycode> OnKeyReleased;
		NOL_API static Observable<Keycode> OnMousePressed;
		NOL_API static Observable<Keycode> OnMouseReleased;

	private:
		static Window*  activeWindow;
		static KeyState stateArray[400];
		static std::vector<int> indexOfClearKeys;

	public:
		NOL_API static bool IfKeyPressed(Keycode keycode);
		NOL_API static bool IfKeyHold(Keycode keycode);
		NOL_API static bool IfKeyReleased(Keycode keycode);
		NOL_API static bool IfMousePressed(Keycode keycode);
		NOL_API static bool IfMouseReleased(Keycode keycode);

	private:
		static void ClearInputFlags();
	};
}

