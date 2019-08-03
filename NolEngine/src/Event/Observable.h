#pragma once

#include "NolAPI.h"
#include "PCH.h"

namespace Nol
{
	template<typename ...Args>
	class Observable
	{
	using Callback = std::function<void(Args... args)>;

	private:
		std::list<Callback> mCallbackList;

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

			for (const auto& callback : mCallbackList)
			{
				if (fnAddress == GetAddress(callback))
					return;
			}

			mCallbackList.push_back(fn);
		}

		void Remove(Callback fn)
		{
			size_t fnAddress = GetAddress(fn);

			typename std::list<Callback>::iterator it;

			for (it = mCallbackList.begin(); it != mCallbackList.end(); it++)
			{
				if (fnAddress == GetAddress(*it))
				{
					mCallbackList.erase(it);
					return;
				}
			}
		}

		void Publish(Args... args)
		{
			if (mCallbackList.size() == 0)
				return;

			for (const auto& callback : mCallbackList)
				callback(args...);
		}	
	};
}