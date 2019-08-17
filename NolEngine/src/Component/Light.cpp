#include "PCH.h"
#include "Light.h"

namespace Nol
{
	Light::Light(const std::string& name) : GameObject(name), color(glm::vec4(1.0f))
	{
	}
}