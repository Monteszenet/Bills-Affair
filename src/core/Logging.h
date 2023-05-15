#pragma once

#include <string>

#define M_DEBUG

#define ERRLEV_LENIENT 0	// Crash only on fatal errors.
#define ERRLEV_MEDIUM 1		// Crash on fatal and normal errors.
#define ERRLEV_STRONG 2		// Crash on fatal errors, normal errors, and warnings.

#define ERROR_TREATMENT_LEVEL ERRLEV_STRONG

#define uint8_t unsigned char

struct MLog
{
	enum MLogType
	{
		LUA,
		INFO,
		WARN,
		ERROR,
		FATAL
	} log_type;

	std::string msg;
};

void InitLogging(std::string path);
void FinaliseLogging();

void FlushLog();
void DumpTrace(int num_trace);

void Log_Process(std::string msg);
void Log_Lua(std::string msg);
void Log_Info(std::string msg);
void Log_Warn(std::string msg);
void Log_Error(std::string msg);
void Log_Fatal(std::string msg);

#ifdef M_DEBUG
#define LOG_PROCESS(msg) Log_Process(msg)
#else
#define LOG_PROCESS(msg)
#endif

#define LOG_LUA(msg) Log_Lua(msg)
#define LOG_INFO(msg) Log_Info(msg)
#define LOG_WARN(msg) Log_Warn(msg)
#define LOG_ERROR(msg) Log_Error(msg)
#define LOG_FATAL(msg) Log_Fatal(msg)

#define LOG_DEMARCATION "[-------------------]"