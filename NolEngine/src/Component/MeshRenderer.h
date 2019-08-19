#pragma once

#include "PCH.h"

#include <glad/glad.h>

#include "Render/Mesh.h"
#include "Render/Shader.h"

#include "Component/Component.h"
#include "Component/Camera.h"
#include "Component/GameObject.h"
#include "Component/Material.h"

namespace Nol
{
	class MeshRenderer : public Component
	{
	private:
		Mesh mesh;
		Shader shader;
		Material material;
		std::function<void()> drawFn;
		std::function<void(const Shader&)> uploadUniformFn;

	public:
		NOL_API MeshRenderer(Mesh& mesh);
		NOL_API MeshRenderer(Mesh& mesh, Shader& shader);
		NOL_API MeshRenderer(Mesh& mesh, Shader& shader, Material& material);
		NOL_API MeshRenderer(const MeshRenderer& other);
		NOL_API virtual ~MeshRenderer() = default;

		NOL_API inline void SetUniformsFn(std::function<void(const Shader&)> uploadUniformFn) { this->uploadUniformFn = uploadUniformFn; }

		NOL_API inline const Mesh& GetMesh() const { return mesh; };
		NOL_API inline const Shader& GetShader() const { return shader; };
		NOL_API inline const Material& GetMaterial() const { return material; };

		NOL_API inline void Render() { drawFn(); }

	private:
		void SetupSelectors();
	};
}

