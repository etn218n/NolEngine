#include <NolEngine.h>

void Foo(Nol::EventArgs args)
{
	int *b = (int*)args.GetSender();
	std::cout << *b << std::endl;
}

Nol::EventHandler handler(Foo);

int main()
{
	Nol::Log::Init();
	
	Nol::Event myEvent;
	//myEvent.AddSubcriber([](Nol::EventArgs e) {std::cout << *(int*)e.GetSender() << std::endl; });
	myEvent.AddSubcriber(Foo);
	myEvent.AddSubcriber(Foo);
	myEvent.RemoveSubcriber(handler);
	myEvent.RemoveSubcriber(handler);
	int a = 5;

	Nol::EventArgs arg((int*)&a);

	myEvent.Invoke(arg);

	Nol::Test::InfiniteLoop();
	return 0;
}