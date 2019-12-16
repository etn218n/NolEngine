#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Window.h"

#include "Event/Observable.h"

namespace Nol
{
	class Engine
	{
	private:
		static Window* gameWindow;
		static Window* testWindow;
		static bool isRunning;

	public:
		NOL_API static Observable<> OnAwake;
		NOL_API static Observable<> OnUpdate;
		NOL_API static Observable<> OnFixedUpdate;
		NOL_API static Observable<> OnLateUpdate;
		NOL_API static Observable<> OnRender;

		NOL_API inline static Window* GameWindow() { return gameWindow; }
		NOL_API inline static bool IsRunning()	   { return isRunning;  }

	public:
		NOL_API static void Start();
		NOL_API static void Update();
		NOL_API static void Stop();
	};
}
