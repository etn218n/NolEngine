#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/GameObject.h"

namespace Nol
{
	class Light : public GameObject
	{
	private:
		glm::vec4 color;

	public:
		NOL_API Light(const std::string& name = "None");
		NOL_API virtual ~Light() = default;

		NOL_API inline void SetColor(const glm::vec4& color) { this->color = color; }

		NOL_API inline glm::vec4& Color() { return color; }
	};
}