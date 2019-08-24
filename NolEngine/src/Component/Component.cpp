#include "PCH.h"
#include "Component.h"

namespace Nol
{
	Component::Component() : owner(nullptr)
	{
	}

	Component::Component(const Component& other) : owner(nullptr)
	{
	}
}