#include "PCH.h"
#include "Light.h"

namespace Nol
{
	Light::Light(const std::string& name, LightType type) :
		GameObject(name), 
		color(glm::vec4(1.0f)),
		type(type) { }

	Light::Light(LightType type) :
		GameObject(name),
		color(glm::vec4(1.0f)),
		type(type){ }
}