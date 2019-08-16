#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Observer.h"

namespace Nol
{
	template<typename ...Args>
	class Observable
	{
	private:
		std::vector<Observer<Args...>> observerList;

	public:
		Observable() { observerList.reserve(5); }
		~Observable() = default;

		void Subcribe(Observer<Args...> newObserver)
		{
			for (auto& observer : observerList)
			{
				if (newObserver.id == observer.id)
					return;
			}

			observerList.push_back(newObserver);
		}

		Observer<Args...>& Subcribe(std::function<void(Args... args)> onNextFn)
		{
			Observer<Args...> observer;

			observer.onNextFn = onNextFn;

			observerList.push_back(observer);

			return observerList.back();
		}

		void Unsubcribe(Observer<Args...>& obs)
		{
			typename std::vector<Observer<Args...>>::iterator it = observerList.begin();

			for (; it != observerList.end(); it++)
			{
				if (it->id == obs.id)
				{
					observerList.erase(it);
					return;
				}
			}
		}

		void Publish(Args... args)
		{
			for (auto& observer : observerList)
				observer.OnNext(args...);
		}	
	};
}