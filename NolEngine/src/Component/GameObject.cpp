#include "PCH.h"
#include "GameObject.h"

namespace Nol
{
	unsigned int GameObject::NextID = 1;

	GameObject::GameObject(const std::string& name) : name(name), id(NextID++), transform(std::make_unique<Transform>())
	{
		transform->owner = this;

		componentMap.insert({ std::type_index(typeid(Transform)), this->transform });
	}

	void GameObject::SetParent(GameObject* parent)
	{
		if (parent == nullptr)
		{
			if (this->parent != nullptr)
				this->parent->RemoveChild(this);

			this->parent = nullptr;
			return;
		}

		this->parent = parent;
		this->parent->AddChild(this);
	}

	void GameObject::AddChild(GameObject* newChild)
	{
		if (newChild->id == this->id)
			return;

		for (const auto& child : childList)
		{
			if (child == newChild)
				return;
		}

		childList.push_back(newChild);

		this->transform->AddChild(newChild->transform.get());
	}

	void GameObject::RemoveChild(GameObject* removedChild)
	{
		int originalSize = childList.size();

		childList.erase(
			std::remove_if(childList.begin(), childList.end(),
				[removedChild](GameObject* child)
				{ 
					return (child->ID() == removedChild->ID());
				}),
			childList.end());

		if (originalSize == childList.size())
			ERR("Failed to remove {0} from {1}'s children.", this->name, removedChild->name);
		else
		{
			removedChild->parent = nullptr;
			INFO("Successful to remove {0} from {1}'s children.", this->name, removedChild->name);
		}

		this->transform->RemoveChild(removedChild->transform.get());
	}
}
