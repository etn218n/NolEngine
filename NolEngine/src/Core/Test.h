#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Event/Observable.h"

#include "Core/Window.h"
#include "Core/Log.h"

#include "Input/Keycode.h"

namespace Nol
{
	class Test
	{
	public:
		NOL_API static Observable<> OnEnterLoop;

	public:
		NOL_API static void SetupLogEventFor(Window* window);
		NOL_API static void InfiniteLoop();
		NOL_API static void PressAnykey();
		NOL_API static void LoadModel(const std::string& filePath);

	private:
		static void LogKeyPress(Window* window, Keycode keycode);
		static void LogKeyHold(Window* window, Keycode keycode);
		static void LogKeyRelease(Window* window, Keycode keycode);

		static void LogMousePress(Window* window, Keycode keycode);
		static void LogMouseRelease(Window* window, Keycode keycode);
	};
}
