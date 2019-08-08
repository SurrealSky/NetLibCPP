#pragma once
#include<Windows.h>

class CLock
{
public:
	void Lock() { EnterCriticalSection(&g_cs); }
	void UnLock() { LeaveCriticalSection(&g_cs); }

public:
	CLock() { InitializeCriticalSection(&g_cs); }
	~CLock() { DeleteCriticalSection(&g_cs); }
private:
	static CRITICAL_SECTION g_cs;
};

CRITICAL_SECTION CLock::g_cs;