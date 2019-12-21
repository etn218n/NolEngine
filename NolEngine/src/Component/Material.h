#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component.h"

#include "Render/Texture.h"
#include "Render/Shader.h"

namespace Nol
{
	class Material : public Component
	{
	public:
		float Shininess;
		glm::vec4 Color;
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		std::vector<Texture> Textures;

	private:
		Shader shader;

	public:
		NOL_API Material();
		NOL_API virtual ~Material() = default;

		NOL_API inline const Shader& GetShader() const { return shader; };
	};
}

