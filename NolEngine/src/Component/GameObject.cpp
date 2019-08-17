#include "PCH.h"
#include "GameObject.h"

namespace Nol
{
	unsigned int GameObject::NextID = 1;

	GameObject::GameObject(const std::string& name) : name(name), id(NextID++)
	{
		transform = new Transform();
		transform->parent = this;

		componentMap.insert(std::pair<std::type_index, Component*>(std::type_index(typeid(Transform)), transform));
	}
}
