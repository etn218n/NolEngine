#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/Transform.h"
#include "Component/Camera.h"
#include "Component/Material.h"

#include "Render/Shader.h"
#include "Render/Texture.h"
#include "Render/UniformLocation.h"

namespace Nol
{
	class ShaderTechnique
	{
	private:
		Shader* shader;
		Camera* camera;
		Material* material;
		Transform* objectTransform;

		std::vector<Texture>& textures;

		UniformLocation uniformLocation;

		std::function<void()> matrixUniformFn; 
		std::function<void()> textureUniformFn;
		std::function<void()> lightUniformFn;
		std::function<void()> materialUniformFn;
		std::pair<long, std::function<void()>> shaderFunctionMap;
		
	public:
		void Apply();

	private:
		static void VoidFn();
		static void TextureFn0x01();
	};
}
