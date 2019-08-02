#include "Test.h"
#include "Log.h"

namespace Nol
{
	void Test::InfiniteLoop()
	{
		INFO("Enter Infinite Loop.");
		while (true);
	}
}
