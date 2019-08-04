#include "Log.h"

namespace Nol
{
	std::shared_ptr<spdlog::logger> Log::engineLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%n]: %v%$");

		engineLogger = spdlog::stdout_color_mt("Engine");
		clientLogger = spdlog::stdout_color_mt("Client");
	}
}
