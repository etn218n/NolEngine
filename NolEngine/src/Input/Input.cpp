#include "PCH.h"
#include "Input.h"

namespace Nol
{
	#pragma region <Initializtion>
	/*-------------------------------------------------------------------------------------------------------*/
	double Input::delayBeforeMouseHold = 0.2;

	Observable<Keycode> Input::OnKeyPressed;
	Observable<Keycode> Input::OnKeyHold;
	Observable<Keycode> Input::OnKeyReleased;

	Observable<Keycode> Input::OnMousePressed;
	Observable<Keycode> Input::OnMouseHold;
	Observable<Keycode> Input::OnMouseReleased;

	KeyState Input::stateArray[400];
	std::vector<int> Input::indexOfUpdatedKeys;
	std::vector<std::pair<KeyState, double>> Input::holdKeys;

	glm::vec2 Input::mousePosition;

	void Input::Init()
	{
		indexOfUpdatedKeys.reserve(10);
		holdKeys.reserve(10);

		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Up, 0)); // Left Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Up, 0)); // Right Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Up, 0)); // Middle Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Up, 0)); // Reserved Mouse button
		holdKeys.push_back(std::pair<KeyState, double>(KeyState::Up, 0)); // Reserved Mouse button
	}
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion

	#pragma region <Input Query Operations>
	/*-------------------------------------------------------------------------------------------------------*/
	bool Input::IfKeyPressed(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfKeyHold(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Hold;
	}
	
	bool Input::IfKeyReleased(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfKeyDown(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Hold || 
			   stateArray[(int)keycode] == KeyState::Down || 
			   stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfKeyUp(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Up || stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfMousePressed(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfMouseHold(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Hold;
	}

	bool Input::IfMouseReleased(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Released;
	}

	bool Input::IfMouseDown(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Hold ||
			   stateArray[(int)keycode] == KeyState::Down ||
			   stateArray[(int)keycode] == KeyState::Pressed;
	}

	bool Input::IfMouseUp(Keycode keycode)
	{
		return stateArray[(int)keycode] == KeyState::Up || stateArray[(int)keycode] == KeyState::Released;
	}
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion

	#pragma region <Core Functionalities>
	/*-------------------------------------------------------------------------------------------------------*/
	void Input::Update(double timeStamp)
	{
		for (size_t i = 0; i < holdKeys.size(); i++)
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

		for (size_t i = indexOfUpdatedKeys.size(); i-- > 0;)
		{
			int keyIndex = indexOfUpdatedKeys[i];

			if (stateArray[keyIndex] == KeyState::Pressed)
				stateArray[keyIndex] = KeyState::Down;
			else
				stateArray[keyIndex] = KeyState::Up;

			indexOfUpdatedKeys.pop_back();
		}
	}
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion
}
