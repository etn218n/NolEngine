#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/GameObject.h"

namespace Nol
{
	enum class LightType
	{
		DirectionalLight = 0,
		PointLight		 = 1,
		SpotLight		 = 2
	};

	class Light : public GameObject
	{
	private:
		glm::vec4 color;
		LightType type;

	public:
		NOL_API Light(const std::string& name = "None", LightType type = LightType::PointLight);
		NOL_API Light(LightType type);
		NOL_API virtual ~Light() = default;

		NOL_API void SetType(LightType type);

		NOL_API inline void SetColor(const glm::vec4& color) { this->color = color; }
		NOL_API inline void SetColor(const glm::vec3& color) { this->color = glm::vec4(color.r, color.b, color.g, 1.0f); }

		NOL_API inline const glm::vec4& Color() const { return color; }
		NOL_API inline const LightType Type()   const { return type;  }
	};
}