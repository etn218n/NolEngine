#include <NolEngine.h>

void Foo(Nol::Window* window)
{
	std::cout << "Focus window: " + window->GetTitle() << std::endl;
}

void Bar(Nol::Window* window, int keycode)
{
	if (keycode == GLFW_KEY_ESCAPE)
		window->Close();
}

template <typename Function>
struct function_traits
	: public function_traits<decltype(&Function::operator())> {
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const> {
	typedef ReturnType(*pointer)(Args...);
	typedef std::function<ReturnType(Args...)> function;
};

template <typename Function>
typename function_traits<Function>::function
to_function(Function & lambda) {
	return static_cast<typename function_traits<Function>::function>(lambda);
}

template <typename Lambda>
size_t getAddress(Lambda lambda) {
	auto function = new decltype(to_function(lambda))(to_function(lambda));
	void * func = static_cast<void *>(function);
	return (size_t)func;
}


int main()
{
	Nol::Log::Init();

	Nol::Window* win = new Nol::Window("Ol", 1280, 720);
	
	auto lambda = [](Nol::Window* win, int keycode)
	{
		INFO("Hello");
	};

	win->OnKeyPressed.Add(Bar);
	//win->OnKeyPressed.Add(lambda);

	while (!win->IsClosed())
	{
		win->Update();
	}

	win->Close();

	Nol::Test::InfiniteLoop();

	return 0;
}