// win32 impl here
#ifndef THREAD_H_
#define THREAD_H_

////////////////////////////////////////////
// Mutex
class TMutex {
private:
    HANDLE MutexHandle;

public:
    TMutex(const bool& LockOnStartP = false);
    ~TMutex();

    // waits so the mutex is released and locks it
    bool Wait(const int& MxMSecs = -1);
	// lock the mutex
	void GetLock();
    // releases the mutex
    bool Release();

    // windows mutex handle
    HANDLE GetThreadHandle() const { return MutexHandle; }
};

////////////////////////////////////////////
// Critical Section
class TCriticalSection {
private:
	CRITICAL_SECTION Cs;

public:
	TCriticalSection();
	~TCriticalSection();

	// start of critical section
	void Enter();
	// try entering critical section, return false when fail
	bool TryEnter();
	// end of critical section
	void Leave();
};

////////////////////////////////////////////
// Blocker 
class TBlocker {
protected:
	HANDLE Event;

public:
	TBlocker();
	~TBlocker();
	
	void Block(int MxMSecs = -1);
	void Release();
};

////////////////////////////////////////////
// Thread
ClassTP(TThread, PThread)// {
protected:
    HANDLE ThreadHandle;
    DWORD ThreadId;

private:
    static DWORD WINAPI EntryPoint(LPVOID pArg);

public:
    TThread();
	TThread(const TThread& Other) { operator=(Other); }

    virtual ~TThread();

	TThread& operator=(const TThread& Other);

    // starts the thread
    void Start();
    // when started the thread calls this function
    virtual void Run() { printf("empty run\n"); };

    // windows thread id
    int GetThreadId() const { return (int)ThreadId; }
    // windows thread handle
    HANDLE GetThreadHandle() const { return ThreadHandle; }

	// join with this thread (wait for it to finish)
	int Join();
	// sleep for given amount of miliseconds
	void Sleep(const int& MSecs);

	// get number of cores in the system
	static int GetCoreCount();
};

// waits until the given thread finishes the execution
// - optionaly can be given a maximal number of miliseconds to wait
template <class TThreadType>
int ThreadWait(TThreadType& Thread, const int& MxMSecs = -1) {
    DWORD dwMilliSeconds = (MxMSecs == -1) ? INFINITE : ((DWORD)MxMSecs);
    const DWORD Res = WaitForSingleObject(Thread.GetThreadHandle(), dwMilliSeconds);
    return (Res == WAIT_ABANDONED) || (Res == WAIT_OBJECT_0);
}

// waits until at least one of threads from the given vector of threads
// finishes the execution
// - optionaly can be given a maximal number of miliseconds to wait
template <class TThreadType>
int ThreadWaitOne(TVec<TThreadType>& ThreadV, const int& MxMSecs = -1) {
    // prepare parameters
    const int Threads = ThreadV.Len();
    const DWORD nCount = (DWORD)Threads;
    const DWORD dwMilliSeconds = (MxMSecs == -1) ? INFINITE : ((DWORD)MxMSecs);
    // create array
    HANDLE* lpHandles = new HANDLE[Threads];
    for (int ThreadN = 0; ThreadN < Threads; ThreadN++) {
        lpHandles[ThreadN] = ThreadV[ThreadN].GetThreadHandle();
    }
    // wait
    const DWORD Res = WaitForMultipleObjects(
        nCount, lpHandles, FALSE, dwMilliSeconds);
    // delete array
    delete lpHandles;
    // check the output and finish
    if (Res == WAIT_TIMEOUT) { return -1; } // timed-out
    return (int)(Res - WAIT_OBJECT_0); // return the index of finished thread
}

////////////////////////////////////////////
// Thread-Vector
template<class TThreadType>
class TThreadV : public TVec<TThreadType> {
public:
	void StartAll() {
		for (int i = 0; i < Len(); i++) {
			(*this)[i].Start();
		}
	}
	int Join() {
		int Status = 0;
		for (int i = 0; i < Len(); i++) {
			Status = ThreadWait<TThreadType>((*this)[i]);
		}
		return Status;
	}
};

#endif /* THREAD_H_ */
