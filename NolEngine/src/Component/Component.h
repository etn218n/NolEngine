#pragma once

#include "NolAPI.h"

namespace Nol
{
	class GameObject;

	class Component
	{
	friend class GameObject;

	protected:
		GameObject* parent;

	public:
		NOL_API Component();
		NOL_API Component(const Component& other);
		NOL_API virtual ~Component() = default;

		NOL_API inline GameObject* GetParent() { return parent; }
	};
}

