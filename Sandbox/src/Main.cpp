#include <NolEngine.h>

using namespace Nol;

void Foo(Keycode keycode)
{
	std::cout << (int)keycode << std::endl;
}

void Bar(Nol::Window* window, Keycode keycode)
{
	if (keycode == Keycode::Escape)
		window->Close();
}

int main()
{
	Log::Init();

	Window* win1 = new Window("First", 200, 200);
	//Window* win2 = new Window("Second", 200, 200);

	while (!win1->IsClosed())
	{
		if (Input::IfKeyDown(Keycode::A))
			INFO("A down.");

		if (Input::IfKeyPressed(Keycode::B))
			INFO("B pressed.");

		if (Input::IfKeyHold(Keycode::C))
			INFO("C hold.");

		if (Input::IfKeyReleased(Keycode::D))
			INFO("D released.");

		if (Input::IfMousePressed(Keycode::LeftMouseButton))
			INFO("Left Mouse Button pressed.");

		if (Input::IfMouseDown(Keycode::RightMouseButton))
			INFO("Right Mouse Button down.");

		if (Input::IfMouseReleased(Keycode::MiddleMouseButton))
			INFO("Middle Mouse Button released.");

		win1->Update();
	}

	Test::PressAnykey();

	return 0;
}