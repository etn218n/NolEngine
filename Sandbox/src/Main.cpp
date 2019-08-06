#include <NolEngine.h>

void Foo(Nol::Window* window)
{
	std::cout << window->GetTitle() << std::endl;
}

void Bar(Nol::Window* window, Keycode keycode)
{
	if (keycode == Keycode::Escape)
		window->Close();
}

int main()
{
	Nol::Log::Init();

	Nol::Window* win1 = new Nol::Window("1");
	Nol::Window* win2 = new Nol::Window("2");
	//win->OnKeyPressed.Add(Bar);
	//win2->OnKeyPressed.Add(Bar);

	win1->OnClosed.Add(Foo);
	win2->OnClosed.Add(Foo);

	while (!win1->IsClosed() || !win2->IsClosed())
	{
		win1->Update();
		win2->Update();
	}

	Nol::Test::InfiniteLoop();

	return 0;
}