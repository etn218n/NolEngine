#include "PCH.h"
#include "Light.h"

namespace Nol
{
	Light::Light(const std::string& name) : 
		GameObject(name), 
		color(glm::vec4(1.0f)),
		ambient(glm::vec3(1.0f)),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f)) { }
}