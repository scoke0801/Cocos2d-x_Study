#pragma once 
#include <Windows.h>
#include <iostream>
#include <string>

constexpr int LOG_BUF_SIZE = 255;
inline void DebugLog(const std::string& msg) { 
	OutputDebugStringA(msg.c_str());
}

inline void DebugLog(const std::wstring& wMsg) {
	OutputDebugStringW(wMsg.c_str());
}

#define SetLogMsg(msg) "FILE - " + std::string(__FILE__) + " / LINE - " + std::to_string(__LINE__) + " / FUNC - " +  std::string(__func__) + " / MSG - " + msg + "\n"