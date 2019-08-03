#pragma once

#include "NolAPI.h"
#include "PCH.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Nol
{
	class NOL_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> mEngineLogger;
		static std::shared_ptr<spdlog::logger> mClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return mEngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return mClientLogger; }
	};
}

#ifdef DEBUG
	#ifdef NOL_ENGINE
		#define TRACE(...) ::Nol::Log::GetEngineLogger()->trace(__VA_ARGS__)
		#define INFO(...)  ::Nol::Log::GetEngineLogger()->info(__VA_ARGS__)
		#define ERR(...)   ::Nol::Log::GetEngineLogger()->error(__VA_ARGS__)
		#define FATAL(...) ::Nol::Log::GetEngineLogger()->fatal(__VA_ARGS__)
		#define WARN(...)  ::Nol::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#else
		#define TRACE(...) ::Nol::Log::GetClientLogger()->trace(__VA_ARGS__)
		#define INFO(...)  ::Nol::Log::GetClientLogger()->info(__VA_ARGS__)
		#define ERR(...)   ::Nol::Log::GetClientLogger()->error(__VA_ARGS__)
		#define FATAL(...) ::Nol::Log::GetClientLogger()->fatal(__VA_ARGS__)
		#define WARN(...)  ::Nol::Log::GetClientLogger()->warn(__VA_ARGS__)
	#endif
#else
	#ifdef NOL_ENGINE
		#define TRACE(...) 
		#define INFO(...)  
		#define ERR(...) 
		#define FATAL(...) 
		#define WARN(...)  
	#else
		#define TRACE(...) 
		#define INFO(...)  
		#define ERR(...) 
		#define FATAL(...) 
		#define WARN(...)  
	#endif
#endif