#include "PCH.h"
#include "Engine.h"

namespace Nol
{
	#pragma region <Initialization>
	/*-------------------------------------------------------------------------------------------------------*/
	bool Engine::isRunning = false;
	Window* Engine::GameWindow = nullptr;

	Observable<> Engine::OnAwake;
	Observable<> Engine::OnUpdate;
	Observable<> Engine::OnFixedUpdate;
	Observable<> Engine::OnLateUpdate;
	Observable<> Engine::OnRender;
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion

	#pragma region <Core Functionalities>
	/*-------------------------------------------------------------------------------------------------------*/
	void Engine::Start()
	{
		if (isRunning)
		{
			WARN("Engine is already started.");
			return;
		}

		isRunning = true;

		Log::Init();

		GameWindow = new Window();
		GameWindow->SetVsync(true);
		GameWindow->Bind();

		GameLoop();
	}

	void Engine::GameLoop()
	{
		OnAwake.Publish();

		while (isRunning)
		{
			if (!GameWindow->IsClosed())
			{
				OnUpdate.Publish();

				// TODO: define fixed update
				OnFixedUpdate.Publish();

				OnLateUpdate.Publish();

				OnRender.Publish();

				Input::UpdateInputState(glfwGetTime());
				GameWindow->Bind();
				GameWindow->Update();
			}
		}
	}

	void Engine::Stop()
	{
		if (!isRunning)
		{
			WARN("Engine has not started.");
			return;
		}

		isRunning = false;
	}
	/*-------------------------------------------------------------------------------------------------------*/
	#pragma endregion
}
