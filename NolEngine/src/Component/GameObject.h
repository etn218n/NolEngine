#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/Component.h"
#include "Component/Transform.h"

namespace Nol
{
	class GameObject
	{
	protected:
		std::unordered_map<std::type_index, std::shared_ptr<Component>> componentMap;
		std::shared_ptr<Transform> transform;
		std::shared_ptr<GameObject> parent;
		std::list<std::shared_ptr<GameObject>> children;
		std::string name;

	private:
		static unsigned int NextID;
		unsigned int id;

	public:
		NOL_API GameObject(const std::string& name = "None");
		NOL_API GameObject(const GameObject& other) = delete;
		NOL_API virtual ~GameObject() = default;

		template<class T>
		void AddComponent(T& component)
		{
			std::shared_ptr<T> newComponent = std::make_shared<T>(component);

			componentMap.insert({ std::type_index(typeid(T)), newComponent });

			newComponent->parent = this;
		}

		template<typename T>
		T* GetComponent()
		{
			return std::dynamic_pointer_cast<T>(componentMap[std::type_index(typeid(T))]).get();
		}

		NOL_API void SetParent(std::shared_ptr<GameObject> parent);
		NOL_API void AddChild(std::shared_ptr<GameObject> child);

		NOL_API inline const unsigned int GetID() const { return id; }

		NOL_API inline Transform* GetTransform() const { return transform.get(); }
		NOL_API inline const int NumberofComponents() const { return componentMap.size(); }
		NOL_API inline const std::string& GetName() const { return name; }
	};
}

