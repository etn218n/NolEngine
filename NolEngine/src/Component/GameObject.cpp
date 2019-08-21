#include "PCH.h"
#include "GameObject.h"

namespace Nol
{
	unsigned int GameObject::NextID = 1;

	GameObject::GameObject(const std::string& name) : name(name), id(NextID++), transform(std::make_unique<Transform>())
	{
		transform->parent = this;

		componentMap.insert({ std::type_index(typeid(Transform)), this->transform });
	}

	void GameObject::SetParent(std::shared_ptr<GameObject> parent)
	{
		if (parent == nullptr)
		{
			WARN("Parent Gameobject is null.");
			return;
		}

		this->parent = parent;
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> child)
	{
		
	}
}
