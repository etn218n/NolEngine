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
		std::unordered_map<std::type_index, Component*> componentMap;
		std::string name;

		Transform* transform;

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
			T* comp = new T(component);

			componentMap.insert(std::pair<std::type_index, Component*>(std::type_index(typeid(T)), comp));

			comp->parent = this;
		}

		template<typename T>
		T* GetComponent()
		{
			return dynamic_cast<T*>(componentMap[std::type_index(typeid(T))]);
		}

		NOL_API inline const unsigned int GetID() const { return id; }

		NOL_API Transform* GetTransform() const { return transform; }
		NOL_API inline const int GetComponentCount() const { return componentMap.size(); }
		NOL_API inline const std::string& GetName() const { return name; }
	};
}

