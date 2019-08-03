#include "Log.h"

namespace Nol
{
	std::shared_ptr<spdlog::logger> Log::mEngineLogger;
	std::shared_ptr<spdlog::logger> Log::mClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%n]: %v%$");

		mEngineLogger = spdlog::stdout_color_mt("Engine");
		mClientLogger = spdlog::stdout_color_mt("Client");
	}
}
