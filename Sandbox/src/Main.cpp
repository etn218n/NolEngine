#include <NolEngine.h>

void Foo(Nol::Keycode keycode)
{
	std::cout << "DMM" << std::endl;
}

void Bar(Nol::Window* window, Nol::Keycode keycode)
{
	if (keycode == Nol::Keycode::Escape)
		window->Close();
}

int main()
{
	Nol::Log::Init();

	Nol::Window* win1 = new Nol::Window("First", 200, 200);
	//Nol::Window* win2 = new Nol::Window("Second", 200, 200);

	win1->OnKeyPressed.Add(Bar);
	//win2->OnKeyPressed.Add(Bar);

	//Nol::Test::SetupLogEventFor(win1);
	//Nol::Test::SetupLogEventFor(win2);

	while (!win1->IsClosed())
	{
		if (Nol::Input::IfKeyPressed(Nol::Keycode::A))
			INFO("A press.");

		if (Nol::Input::IfKeyReleased(Nol::Keycode::B))
			INFO("B released.");

		if (Nol::Input::IfKeyHold(Nol::Keycode::C))
			INFO("C hold.");

		if (Nol::Input::IfMousePressed(Nol::Keycode::LeftMouseButton))
			INFO("Left Mouse Button.");

		win1->Update();

		/*win2->Update();

		if (Nol::Input::IfKeyPressed(Nol::Keycode::A))
			INFO("A press.");

		if (Nol::Input::IfKeyReleased(Nol::Keycode::B))
			INFO("B released.");

		if (Nol::Input::IfKeyHold(Nol::Keycode::C))
			INFO("C hold.");

		if (Nol::Input::IfMousePressed(Nol::Keycode::LeftMouseButton))
			INFO("Left Mouse Button.");*/
	}

	Nol::Test::PressAnykey();

	return 0;
}