#include <NolEngine.h>

void Foo(Nol::Window* window)
{
	std::cout << "Focus window: " + window->GetTitle() << std::endl;
}

void Bar(Nol::Window* window)
{
	std::cout << "Lost window: " + window->GetTitle() << std::endl;
}

int main()
{
	Nol::Log::Init();

	Nol::Window* win = new Nol::Window("Ol", 1280, 720);
	win->OnWindowFocused.Add(Foo);
	win->OnWindowLostFocus.Add(Bar);

	while (win->IsClosed() == false)
	{
		win->Update();
	}

	win->Close();

	Nol::Test::InfiniteLoop();

	return 0;
}