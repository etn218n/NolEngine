#include "PCH.h"
#include "Input.h"

namespace Nol
{
	Window* Input::activeWindow = nullptr;

	double Input::delayBeforeMouseHold = 0.2;

	Observable<Keycode> Input::OnKeyPressed;
	Observable<Keycode> Input::OnKeyHold;
	Observable<Keycode> Input::OnKeyReleased;

	Observable<Keycode> Input::OnMousePressed;
	Observable<Keycode> Input::OnMouseHold;
	Observable<Keycode> Input::OnMouseReleased;

	KeyState Input::stateArray[400];
	std::vector<int> Input::indexOfClearKeys;
	std::vector<std::pair<KeyState, double>> Input::holdKeys;

	// TODO: unreliable code since it depends on initialization order of compiler
	// Need a system to init this Input::instance
	Input* Input::instance = new Input();

	Input::Input()
	{
		indexOfClearKeys.reserve(10);
		holdKeys.reserve(10);

		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Unpressed, 0)); // Left Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Unpressed, 0)); // Right Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Unpressed, 0)); // Middle Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Unpressed, 0)); // Reserved Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Unpressed, 0)); // Reserved Mouse button
	}

	bool Input::IfKeyPressed(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfKeyHold(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Hold;
	}

	bool Input::IfKeyReleased(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfKeyDown(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Pressed || stateArray[(int)keycode] == KeyState::Hold;
	}

	bool Input::IfKeyUp(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Unpressed || stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfMousePressed(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfMouseHold(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Hold;
	}

	bool Input::IfMouseReleased(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfMouseDown(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Pressed || stateArray[(int)keycode] == KeyState::Hold;
	}

	bool Input::IfMouseUp(Keycode keycode)
	{
		if (activeWindow == nullptr)
			return false;

		return stateArray[(int)keycode] == KeyState::Unpressed || stateArray[(int)keycode] == KeyState::Released;
	}

	void Input::ClearInputFlags(double timeStamp)
	{
		for (int i = 0; i < holdKeys.size(); i++)
		{
			if (holdKeys[i].first == KeyState::Pressed)
			{
				if (timeStamp - holdKeys[i].second > delayBeforeMouseHold)
				{
					stateArray[i] = KeyState::Hold;
					OnMouseHold.Publish((Keycode)i);
				}
			}
		}

		for (int i = indexOfClearKeys.size() - 1; i >= 0; i--)
		{
			int keyIndex = indexOfClearKeys[i];

			stateArray[keyIndex] = KeyState::Unpressed;

			indexOfClearKeys.pop_back();
		}
	}
}
