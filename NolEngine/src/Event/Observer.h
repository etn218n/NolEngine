#pragma once

#include "PCH.h"
#include "NolAPI.h"

namespace Nol
{
	template<typename ...Args>
	class Observable;

	template<typename ...Args>
	class Observer
	{
	template<typename ...Args>
	friend class Observable;

	private:
		static unsigned int NextID;

		unsigned int id;
		std::function<void(Args... args)> onNextFn;

	public:
		Observer() : id(NextID++) { };
		Observer(std::function<void(Args... args)> onNextFn) : id(NextID++), onNextFn(onNextFn) { };
		~Observer() = default;

		inline const unsigned int GetID() const { return id; }

	private:
		inline void OnNext(Args... args) const { onNextFn(args...); }
	};

	template<typename ...Args>
	unsigned int Observer<Args...>::NextID = 1;
}