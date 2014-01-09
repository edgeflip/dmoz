#ifndef THREAD_H
#define THREAD_H

#include <base.h>

#if defined(GLib_WIN)

#include "arch/win/thread_win.h"

#elif defined(GLib_UNIX)

#include "arch/posix/thread_posix.h"

#else

// no support for threads in non-Win and non-Unix systems

#endif

ClassTPE(TInterruptibleThread, PInterruptipleThread, TThread)// {
protected:
	// Use for interrupting and waiting
	TBlocker SleeperBlocker;
public:
	TInterruptibleThread(): TThread() { }
	TInterruptibleThread(const TInterruptibleThread& Other) { operator=(Other); }
	TInterruptibleThread& operator=(const TInterruptibleThread& Other);
	
	void Interrupt();
	void WaitForInterrupt(const int Msecs = INFINITE);
};

////////////////////////////////////////////
// Lock 
//   Wrapper around criticla section, which automatically enters 
//   on construct, and leaves on scope unwinding (destruct)
class TLock {
private:
	TCriticalSection& CriticalSection;
public:
	TLock(TCriticalSection& _CriticalSection):
		CriticalSection(_CriticalSection) { CriticalSection.Enter(); }
	~TLock() { CriticalSection.Leave(); }
};

#endif
