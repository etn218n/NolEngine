#include "PCH.h"
#include "Material.h"

namespace Nol
{
	Material::Material() :
		Color(glm::vec4(1.0f)),
		Ambient(glm::vec3(0.2f)),
		Diffuse(glm::vec3(1.0f)),
		Specular(glm::vec3(1.0f)),
		Shininess(32.0f) { }
}

