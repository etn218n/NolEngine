#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component.h"

namespace Nol
{
	class Material : public Component
	{
	private:
		glm::vec4 color;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;

	public:
		NOL_API Material();
		NOL_API virtual ~Material() = default;

		NOL_API inline void SetShininess(float shininess)		   { this->shininess = shininess; }
		NOL_API inline void SetColor(const glm::vec4& color)	   { this->color = color;		  }
		NOL_API inline void SetAmbient(const glm::vec3& ambient)   { this->ambient = ambient;     }
		NOL_API inline void SetDiffuse(const glm::vec3& diffuse)   { this->diffuse = diffuse;     }
		NOL_API inline void SetSpecular(const glm::vec3& specular) { this->specular = specular;   }

		NOL_API inline const float Shininess()	   const { return shininess; }
		NOL_API inline const glm::vec4& Color()    const { return color;	 }
		NOL_API inline const glm::vec3& Ambient()  const { return ambient;   }
		NOL_API inline const glm::vec3& Diffuse()  const { return diffuse;   }
		NOL_API inline const glm::vec3& Specular() const { return specular;  }
	};
}

