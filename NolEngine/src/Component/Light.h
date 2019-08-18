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
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

	public:
		NOL_API Light(const std::string& name = "None");
		NOL_API virtual ~Light() = default;

		NOL_API inline void SetColor(const glm::vec4& color)	   { this->color = color;       }
		NOL_API inline void SetAmbient(const glm::vec3& ambient)   { this->ambient = ambient;   }
		NOL_API inline void SetDiffuse(const glm::vec3& diffuse)   { this->diffuse = diffuse;   }
		NOL_API inline void SetSpecular(const glm::vec3& specular) { this->specular = specular; }

		NOL_API inline glm::vec4& Color()    { return color;    }
		NOL_API inline glm::vec3& Ambient()  { return ambient;  }
		NOL_API inline glm::vec3& Diffuse()  { return diffuse;  }
		NOL_API inline glm::vec3& Specular() { return specular; }
	};
}