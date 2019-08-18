#include "PCH.h"
#include "Time.h"

namespace Nol
{
	double Time::Now()
	{
		return glfwGetTime();
	}
}