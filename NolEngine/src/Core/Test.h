#pragma once

#include "NolAPI.h"
#include "PCH.h"
#include "Event/Observable.h"

namespace Nol
{
	class NOL_API Test
	{
	public:
		static Observable<> OnEnterLoop;

	public:
		static void InfiniteLoop();
	};
}
