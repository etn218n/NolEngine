#include <NolEngine.h>

void Foo(Nol::Window* window)
{
	std::cout << "Foo window: " + window->GetTitle() << std::endl;
}

void Bar()
{
	std::cout << "Bar" << std::endl;
}

int main()
{
	Nol::Log::Init();

	Nol::Window* win = new Nol::Window("Ol", 1280, 720);
	win->OnWindowClosed.Add(Foo);

	while (win->IsClosed() == false)
	{
		win->Update();
	}

	win->Close();

	Nol::Test::InfiniteLoop();

	return 0;
}