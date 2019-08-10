#include "PCH.h"
#include "GameObject.h"

namespace Nol
{
	GameObject::GameObject(const std::string& name) : name(name)
	{
		transform = new Transform();
		transform->parent = this;

		componentMap.insert(std::pair<std::type_index, Component*>(std::type_index(typeid(Transform)), transform));
	}
}
