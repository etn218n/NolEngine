#include "Event.h"

namespace Nol
{
	Event::Event()
	{
	}
	Event::~Event()
	{
	}

	void Event::Invoke(EventArgs args)
	{
		if (subcriberList.size() == 0)
			return;

		for (auto& subcriber : subcriberList)
			subcriber.Invoke(args);
	}

	void Event::AddSubcriber(EventHandler handler)
	{
		// TODO: implement ID for eventhandler

		subcriberList.push_back(handler);
	}

	void Event::AddSubcriber(std::function<void(EventArgs)> fn)
	{
		subcriberList.push_back(EventHandler(fn));
	}

	void Event::RemoveSubcriber(EventHandler handler)
	{
		subcriberList.remove(handler);
	}
}