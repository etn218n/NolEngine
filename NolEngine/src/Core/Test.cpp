#include "Test.h"

namespace Nol
{
	Observable<> Test::OnEnterLoop;

	void Foo() {}

	void Test::InfiniteLoop()
	{
		INFO("Enter Infinite Loop.");

		OnEnterLoop.Publish();

		while (true);
	}
}
