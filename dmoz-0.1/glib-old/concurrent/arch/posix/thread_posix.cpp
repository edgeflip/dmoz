/*
 * thread.cpp
 *
 *  Created on: May 24, 2010
 *      Author: tadej
 */
#include "thread_posix.h"
#include <time.h>
#include <pthread.h>


////////////////////////////////////////////
// Mutex
TMutex::TMutex(const bool& LockOnStartP) {
	pthread_mutexattr_init(&Attributes);
	pthread_mutexattr_setpshared(&Attributes, PTHREAD_PROCESS_SHARED);
	pthread_mutex_init(&MutexHandle, &Attributes);
}

TMutex::~TMutex() {
    pthread_mutexattr_destroy(&Attributes);
    pthread_mutex_destroy(&MutexHandle);
}

bool TMutex::Wait(const int& MxMSecs) {
	timespec waitTime;
	long nano = MxMSecs * 1000000;
	waitTime.tv_nsec = nano;
	return pthread_mutex_timedlock(&MutexHandle, &waitTime) == 0;
}

bool TMutex::Release() {
	return pthread_mutex_unlock(&MutexHandle) == 0;
}

void TMutex::GetLock() {
	pthread_mutex_lock(&MutexHandle);
}

TCriticalSection::TCriticalSection() {
	pthread_mutex_init(&Cs, NULL);
}
TCriticalSection::~TCriticalSection() {
	pthread_mutex_destroy(&Cs);
}
void TCriticalSection::Enter() {
	pthread_mutex_lock(&Cs);
}
bool TCriticalSection::TryEnter() {
	return pthread_mutex_trylock(&Cs);
}
void TCriticalSection::Leave() {
	pthread_mutex_unlock(&Cs);
}

TBlocker::TBlocker() {
	/*Event = CreateEvent(
        NULL,               // default security attributes
        false,               // auto-reset event
        false,              // initial state is nonsignaled
        NULL);	// object name
	IAssert(Event != NULL);*/
	pthread_cond_init(&Event, NULL);
	pthread_mutex_init(&Mutex, NULL);
}

TBlocker::~TBlocker() {
	pthread_cond_destroy(&Event);
	pthread_mutex_destroy(&Mutex);
}

void TBlocker::Block(int Msecs) {
	timespec waitTime;
	long nano = Msecs * 1000000;
	waitTime.tv_nsec = nano;
	pthread_cond_timedwait(&Event, &Mutex, &waitTime);
}
void TBlocker::Release() {
	pthread_cond_broadcast(&Event);
}


////////////////////////////////////////////
// Thread
void * TThread::EntryPoint(void * pArg) {
    TThread *pThis = (TThread *)pArg;
    pThis->Run();
    return 0;
}

TThread::TThread(): ThreadHandle(), ThreadId(0) { }

TThread::~TThread() {
}

TThread &TThread::operator =(const TThread& Other) {
	ThreadHandle = Other.ThreadHandle;
	ThreadId = Other.ThreadId;
	return *this;
}

void TThread::Start() {
    // create new thread
	int code = pthread_create(
			&ThreadHandle,	// Handle
			NULL,			// Attributes
			EntryPoint,		// Thread func
			this			// Arg
	);
	EAssert(code == 0);


}

int TThread::Join() {
	pthread_join(ThreadHandle, NULL);
	return 0;
}


int TThread::GetCoreCount() {
	int NumCpu;
	#if defined(GLib_LINUX) || defined(GLIB_SOLARIS) || defined(GLib_CYGWIN)
		NumCpu = sysconf( _SC_NPROCESSORS_ONLN );
	#elif defined(GLib_BSD)
		nt mib[4];
		size_t len;

		/* set the mib for hw.ncpu */
		mib[0] = CTL_HW;
		mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;

		/* get the number of CPUs from the system */
		sysctl(mib, 2, &NumCpu, &len, NULL, 0);

		if( numCPU < 1 )
		{
			 mib[1] = HW_NCPU;
			 sysctl( mib, 2, &NumCpu, &len, NULL, 0 );

			 if( NumCpu < 1 )
			 {
				  NumCpu = 1;
			 }
		}
	#else
		NumCpu = 1;
	#endif

	return NumCpu;
}