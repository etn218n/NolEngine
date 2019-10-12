#include "PCH.h"
#include "Engine.h"

namespace Nol
{
	bool Engine::IsRunning = false;
	Window* Engine::MainWindow = nullptr;

	Observable<> Engine::OnAwake;
	Observable<> Engine::OnUpdate;
	Observable<> Engine::OnFixedUpdate;
	Observable<> Engine::OnLateUpdate;
	Observable<> Engine::OnRender;

	void Engine::Start()
	{
		if (IsRunning)
		{
			WARN("Engine is already started.");
			return;
		}

		IsRunning = true;

		Log::Init();

		MainWindow = new Window();
		MainWindow->SetVsync(true);
		MainWindow->Bind();

		GameLoop();
	}

	void Engine::GameLoop()
	{
		OnAwake.Publish();

		while (IsRunning)
		{
			if (!MainWindow->IsClosed())
				MainWindow->Update();

			OnUpdate.Publish();

			// define fixed update
			OnFixedUpdate.Publish();

			OnLateUpdate.Publish();

			OnRender.Publish();
		}
	}

	void Engine::Stop()
	{
		if (!IsRunning)
		{
			WARN("Engine has not started.");
			return;
		}

		IsRunning = false;
	}
}
