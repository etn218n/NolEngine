#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Scene.h"
#include "UniformBuffer.h"

namespace Nol
{
	class Renderer
	{
	private:
		static std::shared_ptr<Scene> activeScene;
		static UniformBuffer* cameraBuffer;

	public:
		//NOL_API Renderer() = delete;
		//NOL_API Renderer(std::shared_ptr<Scene> scene);
		NOL_API static void Init();
		//NOL_API virtual ~Renderer() = default;

		NOL_API static void SetScene(std::shared_ptr<Scene> scene);

		NOL_API static void Update();
	};
}

