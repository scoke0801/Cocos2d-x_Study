#pragma once 
#include <Windows.h>
#include <iostream>
#include <string>
namespace Utils {
	constexpr int LOG_BUF_SIZE = 255;
	inline void DebugLog(const std::string& msg) {
		OutputDebugStringA(msg.c_str());
	}

	inline void DebugLog(const std::wstring& wMsg) {
		OutputDebugStringW(wMsg.c_str());
	}

	template<typename ... Args>
	std::string string_format(const std::string& format, Args ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		if (size <= 0) { return "STRING_FORMAT_ERROR\n"; }
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}
#define SetLogMsg(msg) "FILE - " + std::string(__FILE__) + " / LINE - " + std::to_string(__LINE__) + " / FUNC - " +  std::string(__func__) + " / MSG - " + msg + "\n"
}
