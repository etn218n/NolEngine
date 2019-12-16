#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Input/Keycode.h"

#include "Core/Log.h"
#include "Core/Window.h"

#include "Event/Observable.h"

namespace Nol
{
	enum KeyState { Up, Pressed, Down, Hold, Released };

	class Input
	{
	friend class Window;
	friend class Engine;

	public:
		NOL_API static Observable<Keycode> OnKeyPressed;
		NOL_API static Observable<Keycode> OnKeyHold;
		NOL_API static Observable<Keycode> OnKeyReleased;

		NOL_API static Observable<Keycode> OnMousePressed;
		NOL_API static Observable<Keycode> OnMouseHold;
		NOL_API static Observable<Keycode> OnMouseReleased;

	private:
		static double delayBeforeMouseHold;
		static KeyState stateArray[400];
		static std::vector<int> indexOfUpdatedKeys;
		static std::vector<std::pair<KeyState, double>> holdKeys;
		static glm::vec2 mousePosition;

	public:
		NOL_API static bool IfKeyPressed(Keycode keycode);
		NOL_API static bool IfKeyHold(Keycode keycode);
		NOL_API static bool IfKeyReleased(Keycode keycode);
		NOL_API static bool IfKeyDown(Keycode keycode);
		NOL_API static bool IfKeyUp(Keycode keycode);

		NOL_API static bool IfMousePressed(Keycode keycode);
		NOL_API static bool IfMouseHold(Keycode keycode);
		NOL_API static bool IfMouseReleased(Keycode keycode);
		NOL_API static bool IfMouseDown(Keycode keycode);
		NOL_API static bool IfMouseUp(Keycode keycode);

		NOL_API static inline glm::vec2& GetMousePostion() { return mousePosition; }

	private:
		static void Init();
		static void Update(double timeStamp);
	};
}

