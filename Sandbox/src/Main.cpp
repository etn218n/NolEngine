#include <NolEngine.h>

void Foo()
{
	std::cout << "Foo" << std::endl;
}
void Bar()
{
	std::cout << "Bar" << std::endl;
}

int main()
{
	Nol::Log::Init();

	Nol::Test::OnEnterLoop.Add(Foo);
	Nol::Test::OnEnterLoop.Add(Bar);
	Nol::Test::OnEnterLoop.Remove(Foo);
	Nol::Test::OnEnterLoop.Add(Foo);

	Nol::Test::InfiniteLoop();
	return 0;
}