#pragma once

#include "PCH.h"
#include "NolAPI.h"

namespace Nol
{
	template<typename ...Args>
	class Observable
	{
	using Callback = std::function<void(Args... args)>;

	private:
		std::list<Callback> callbackList;

	private:
		template<typename T, typename... U>
		size_t GetAddress(std::function<T(U...)> f)
		{
			typedef T(fnType)(U...);
			fnType ** fnPointer = f.template target<fnType*>();
			return (size_t)*fnPointer;
		}

	public:
		Observable() {}

		void Add(Callback fn)
		{
			size_t fnAddress = GetAddress(fn);

			for (const auto& callback : callbackList)
			{
				if (fnAddress == GetAddress(callback))
					return;
			}

			callbackList.push_back(fn);
		}

		void Remove(Callback fn)
		{
			size_t fnAddress = GetAddress(fn);

			typename std::list<Callback>::iterator it;

			for (it = callbackList.begin(); it != callbackList.end(); it++)
			{
				if (fnAddress == GetAddress(*it))
				{
					callbackList.erase(it);
					return;
				}
			}
		}

		void Publish(Args... args)
		{
			if (callbackList.size() == 0)
				return;

			for (const auto& callback : callbackList)
				callback(args...);
		}	
	};
}