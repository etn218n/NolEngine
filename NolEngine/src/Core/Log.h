#pragma once

#include "NolAPI.h"
#include <memory>


#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Nol
{
	class NOL_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> _engineLogger;
		static std::shared_ptr<spdlog::logger> _clientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return _engineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return _clientLogger; }
	};
}

#ifdef DEBUG
	#define _TRACE(...) ::Nol::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define _INFO(...)  ::Nol::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define _ERR(...)   ::Nol::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define _FATAL(...) ::Nol::Log::GetEngineLogger()->fatal(__VA_ARGS__)
	#define _WARN(...)  ::Nol::Log::GetEngineLogger()->warn(__VA_ARGS__)

	#define TRACE(...) ::Nol::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define INFO(...)  ::Nol::Log::GetClientLogger()->info(__VA_ARGS__)
	#define ERR(...)   ::Nol::Log::GetClientLogger()->error(__VA_ARGS__)
	#define FATAL(...) ::Nol::Log::GetClientLogger()->fatal(__VA_ARGS__)
	#define WARN(...)  ::Nol::Log::GetClientLogger()->warn(__VA_ARGS__)
#else
	#define _TRACE(...) 
	#define _INFO(...)  
	#define _ERR(...) 
	#define _FATAL(...) 
	#define _WARN(...)  

	#define TRACE(...) 
	#define INFO(...)  
	#define ERR(...) 
	#define FATAL(...) 
	#define WARN(...)  
#endif