#pragma once

#include "JavaEngine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace JavaEngine {

	class JE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define JE_CORE_TRACE(...)	::JavaEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JE_CORE_INFO(...)	::JavaEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JE_CORE_WARN(...)	::JavaEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JE_CORE_ERROR(...)	::JavaEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JE_CORE_FATAL(...)	::JavaEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define JE_TRACE(...)	::JavaEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JE_INFO(...)	::JavaEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define JE_WARN(...)	::JavaEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JE_ERROR(...)	::JavaEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define JE_FATAL(...)	::JavaEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)