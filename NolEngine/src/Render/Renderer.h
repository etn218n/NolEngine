#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Scene.h"
#include "Uniform.h"

namespace Nol
{
	class Renderer
	{
	private:
		std::shared_ptr<Scene> scene;

	public:
		NOL_API Renderer() = default;
		NOL_API Renderer(std::shared_ptr<Scene> scene);
		NOL_API virtual ~Renderer() = default;

		NOL_API void SetScene(std::shared_ptr<Scene> scene);

		NOL_API void Update();
	};
}

