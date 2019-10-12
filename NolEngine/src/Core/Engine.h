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
		static bool IsRunning;
		static Window* MainWindow;

	public:
		NOL_API static Observable<> OnAwake;
		NOL_API static Observable<> OnUpdate;
		NOL_API static Observable<> OnFixedUpdate;
		NOL_API static Observable<> OnLateUpdate;
		NOL_API static Observable<> OnRender;

	public:
		NOL_API static void Start();
		NOL_API static void GameLoop();
		NOL_API static void Stop();
	};
}

