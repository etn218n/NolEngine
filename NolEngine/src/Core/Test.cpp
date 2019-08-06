#include "PCH.h"
#include "Test.h"

#include <conio.h>

namespace Nol
{
	Observable<> Test::OnEnterLoop;

	void Test::LogKeyPress(Window* window, Keycode keycode)	  { INFO("(Window \"{0}\") Key {1} pressed.", window->GetTitle(), (int)keycode);  }
	void Test::LogKeyHold(Window* window, Keycode keycode)	  { INFO("(Window \"{0}\") Key {1} held.", window->GetTitle(), (int)keycode);	  }
	void Test::LogKeyRelease(Window* window, Keycode keycode) { INFO("(Window \"{0}\") Key {1} released.", window->GetTitle(), (int)keycode); }

	void Test::LogMousePress(Window * window, Keycode keycode)   { INFO("(Window \"{0}\") Mouse button {1} pressed.",  window->GetTitle(), (int)keycode); }
	void Test::LogMouseRelease(Window * window, Keycode keycode) { INFO("(Window \"{0}\") Mouse button {1} released.", window->GetTitle(), (int)keycode); }

	void Test::SetupLogEventFor(Window* window)
	{
		window->OnKeyPressed.Add(LogKeyPress);
		window->OnKeyHold.Add(LogKeyHold);
		window->OnKeyReleased.Add(LogKeyRelease);

		window->OnMousePressed.Add(LogMousePress);
		window->OnMouseReleased.Add(LogMouseRelease);
	}

	void Test::InfiniteLoop()
	{
		INFO("Enter Infinite Loop.");

		OnEnterLoop.Publish();

		while (true);
	}

	void Test::PressAnykey()
	{
		_getch();
	}
}
