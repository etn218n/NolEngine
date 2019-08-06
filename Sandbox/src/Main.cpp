#include <NolEngine.h>

void Foo(Nol::Window* window)
{
	std::cout << window->GetTitle() << std::endl;
}

void Bar(Nol::Window* window, Nol::Keycode keycode)
{
	if (keycode == Nol::Keycode::Escape)
		window->Close();
}

int main()
{
	Nol::Log::Init();

	Nol::Window* win1 = new Nol::Window("Testing 1");
	//Nol::Window* win2 = new Nol::Window("2");

	win1->OnKeyPressed.Add(Bar);
	//win2->OnKeyPressed.Add(Bar);

	Nol::Test::SetupLogEventFor(win1);

	while (!win1->IsClosed())
	{
		win1->Update();

		//if (Nol::Input::IfKeyReleased(Nol::Keycode::A))
		//	INFO("A pressed");
	}

	Nol::Test::PressAnykey();

	return 0;
}