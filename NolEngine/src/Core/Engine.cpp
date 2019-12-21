#include "PCH.h"
#include "Engine.h"

namespace Nol
{
	#pragma region <Initialization>
	/*-------------------------------------------------------------------------------------------------------*/
	bool Engine::isRunning = false;
	Window* Engine::gameWindow = nullptr;
	Window* Engine::testWindow = nullptr;

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

		gameWindow = new Window("Game", 800, 600, false, nullptr);
		gameWindow->Bind();

		Input::Init();
		Renderer::Init();

		OnAwake.Publish();

		Update();
	}

	void Engine::Update()
	{
		while (isRunning)
		{
			double currentTime = glfwGetTime();

			OnFixedUpdate.Publish();
			OnUpdate.Publish();
			OnLateUpdate.Publish();

			if (!gameWindow->IsClosed())
			{
				gameWindow->Bind();

				Renderer::Update();
				OnRender.Publish();

				gameWindow->SwapBuffer();
			}

			Input::Update(currentTime);
			glfwPollEvents();
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
