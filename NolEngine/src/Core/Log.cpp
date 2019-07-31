#include "Log.h"

namespace Nol
{
	std::shared_ptr<spdlog::logger> Log::_engineLogger;
	std::shared_ptr<spdlog::logger> Log::_clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%n]: %v%$");

		_engineLogger = spdlog::stdout_color_mt("Engine");
		_clientLogger = spdlog::stdout_color_mt("Client");
	}
}
