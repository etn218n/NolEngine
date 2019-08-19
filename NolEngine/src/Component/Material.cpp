#include "PCH.h"
#include "Material.h"

namespace Nol
{
	Material::Material() :
		color(glm::vec4(1.0f)),
		ambient(glm::vec3(0.2f)),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f)),
		shininess(32.0f) { }
}

