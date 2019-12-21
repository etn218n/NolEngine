#pragma once

#include "PCH.h"

#include "Render/Mesh.h"
#include "Component/Material.h"
#include "Render/Shader.h"

#include "Component/Component.h"

namespace Nol
{
	class ObjectRenderer3D : Component
	{
	private:
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Material> material;

		std::function<void()> drawFn;
		std::function<void()> uploadTextureUniform;
		std::function<void()> uploadMaterialUniform;

	public:
		ObjectRenderer3D(std::shared_ptr<Shader> shader, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

		NOL_API inline void Draw() { drawFn(); };
		NOL_API inline void UploadUniform() { drawFn(); };

	private:
		void DrawArray();
		void DrawElement();
	};
}
