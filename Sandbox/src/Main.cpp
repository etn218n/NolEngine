#include <NolEngine.h>

int main()
{
	Nol::Log::Init();
	INFO("Hi");
	Nol::Test::InfiniteLoop();
	return 0;
}