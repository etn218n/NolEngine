#pragma once

#include "PCH.h"
#include "NolAPI.h"
#include "Event/Observable.h"

namespace Nol
{
	class Test
	{
	public:
		NOL_API static Observable<> OnEnterLoop;

	public:
		NOL_API static void InfiniteLoop();
	};
}
