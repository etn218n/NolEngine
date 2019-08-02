#pragma once

#include "NolAPI.h"
#include "PCH.h"

namespace Nol
{
	class NOL_API EventArgs
	{
	private:
		void* _sender;

	public:
		EventArgs(void* sender) : _sender(sender) {}
		inline void* GetSender() const { return _sender; }
	};

	class NOL_API EventHandler
	{
	private:
		std::function<void(EventArgs)> _fn;

	private:
		template<typename T, typename... U>
		size_t GetAddress(std::function<T(U...)> f) 
		{
			typedef T(fnType)(U...);
			fnType ** fnPointer = f.template target<fnType*>();
			return (size_t)*fnPointer;
		}

	public:
		EventHandler(std::function<void(EventArgs)> fn) : _fn(fn) { }

		inline void Invoke(EventArgs args) { _fn(args); }
		inline bool operator==(const EventHandler& other) { return GetAddress(_fn) == GetAddress(other._fn); }
		inline size_t GetFnAddress() { return GetAddress(_fn); }
	};

	class NOL_API Event
	{
	private:
		std::list<EventHandler> subcriberList;

	public:
		Event();
		~Event();

		void Invoke(EventArgs args);
		void AddSubcriber(EventHandler handler);
		void AddSubcriber(std::function<void(EventArgs)> fn);
		void RemoveSubcriber(EventHandler handler);
	};

	
}
