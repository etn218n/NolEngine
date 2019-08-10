#pragma once

#include "PCH.h"

#include <glad/glad.h>

#include "Render/Mesh.h"
#include "Render/Shader.h"

namespace Nol
{
	class MeshRenderer
	{
	private:
		Mesh mesh;
		Shader shader;
		std::function<void()> draw;

	public:
		NOL_API MeshRenderer(Mesh& mesh);
		NOL_API MeshRenderer(Mesh& mesh, Shader& shader);
		NOL_API virtual ~MeshRenderer() = default;

		NOL_API void Render();
	};
}

