#include "PCH.h"
#include "Input.h"

namespace Nol
{
	Window* Input::activeWindow = nullptr;

	Observable<Keycode> Input::OnKeyPressed;
	Observable<Keycode> Input::OnKeyHold;
	Observable<Keycode> Input::OnKeyReleased;

	Observable<Keycode> Input::OnMousePressed;
	Observable<Keycode> Input::OnMouseReleased;

	KeyState Input::stateArray[400];
	std::vector<int> Input::indexOfClearKeys;

	bool Input::IfKeyPressed(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		return stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfKeyHold(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		return stateArray[(int)keycode] == KeyState::Hold || stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfKeyReleased(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		return stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfMousePressed(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		return stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfMouseReleased(Keycode keycode)
	{
		if (activeWindow == nullptr)
		{
			WARN("Input::activeWindow is NULL.");
			return false;
		}

		return stateArray[(int)keycode] == KeyState::Released;
	}

	void Input::ClearInputFlags()
	{
		for (int i = indexOfClearKeys.size() - 1; i >= 0; i--)
		{
			int keyIndex = indexOfClearKeys[i];

			stateArray[keyIndex] = KeyState::Unpressed;

			indexOfClearKeys.pop_back();
		}
	}
}
