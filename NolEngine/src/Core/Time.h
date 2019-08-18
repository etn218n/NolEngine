#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include <glfw/glfw3.h>

namespace Nol
{
	class Time
	{
	public:
		NOL_API static double Now();
	};
}