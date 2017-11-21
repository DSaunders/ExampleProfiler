#include <cor.h>
#include <corprof.h>
#include <corhlpr.h>

/*	
	This header file also includes the implementation of methods.
	
	You do not need to structure your profiler this way, but it is useful in 
	this example project as it allows us to show only the implementation-specific 
	code in the .cpp file. This makes it easier to separate the code you need to 
	write yourself, from the code that is common in every profiler.

	To implement a method, remove the implementation here (e.g. '{ return S_OK; }'),
	and write the implementation in the .cpp file instead
 */

class ExampleProfiler : public ICorProfilerCallback3
{
public:
	ExampleProfiler();
	~ExampleProfiler();

	// IUnknown interface implementation
	STDMETHODIMP_(ULONG) AddRef() { return InterlockedIncrement(&refCount); }
	STDMETHODIMP_(ULONG) Release() { auto ret = InterlockedDecrement(&refCount); if (ret <= 0) delete(this); return ret; }

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override
	{
		if (riid == __uuidof(ICorProfilerCallback3) ||
			riid == __uuidof(ICorProfilerCallback2) ||
			riid == __uuidof(ICorProfilerCallback) ||
			riid == IID_IUnknown)
		{
			*ppvObject = this;
			this->AddRef();
			return S_OK;
		}

		*ppvObject = nullptr;
		return E_NOINTERFACE;
	}

	// ICorProfilerCallback
	STDMETHODIMP Initialize(IUnknown * pICorProfilerInfoUnk) { return InitializeForAttach(pICorProfilerInfoUnk, NULL, -1); };
	STDMETHODIMP Shutdown() { if (profilerInfo != NULL) profilerInfo->Release(); profilerInfo = NULL; return S_OK; }

	// ICorProfilerCallback2
	STDMETHODIMP ThreadNameChanged(ThreadID threadId, ULONG cchName, WCHAR* name) { return S_OK; };
	STDMETHODIMP GarbageCollectionStarted(int cGenerations, BOOL generationCollected[], COR_PRF_GC_REASON reason) { return S_OK; };;
	STDMETHODIMP SurvivingReferences(ULONG cSurvivingObjectIDRanges, ObjectID objectIDRangeStart[], ULONG cObjectIDRangeLength[]) { return S_OK; };
	STDMETHODIMP GarbageCollectionFinished(void);  // This is implemented in the .cpp file
	STDMETHODIMP FinalizeableObjectQueued(DWORD finalizerFlags, ObjectID objectID) { return S_OK; };
	STDMETHODIMP RootReferences2(ULONG cRootRefs, ObjectID rootRefIds[], COR_PRF_GC_ROOT_KIND rootKinds[], COR_PRF_GC_ROOT_FLAGS rootFlags[], UINT_PTR rootIds[]) { return S_OK; };
	STDMETHODIMP HandleCreated(GCHandleID handleId, ObjectID initialObjectId) { return S_OK; };
	STDMETHODIMP HandleDestroyed(GCHandleID handleId) { return S_OK; };

	// ICorProfilerCallback3
	HRESULT STDMETHODCALLTYPE InitializeForAttach(IUnknown *pCorProfilerInfoUnk, void *pvClientData, UINT cbClientData);
	HRESULT STDMETHODCALLTYPE ProfilerAttachComplete(void) { return S_OK; };
	HRESULT STDMETHODCALLTYPE ProfilerDetachSucceeded(void) { return Shutdown(); }

	STDMETHODIMP AppDomainCreationStarted(AppDomainID appDomainId) { return S_OK; };
	STDMETHODIMP AppDomainCreationFinished(AppDomainID appDomainId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP AppDomainShutdownStarted(AppDomainID appDomainId) { return S_OK; };
	STDMETHODIMP AppDomainShutdownFinished(AppDomainID appDomainId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP AssemblyLoadStarted(AssemblyID assemblyId) { return S_OK; };
	STDMETHODIMP AssemblyLoadFinished(AssemblyID assemblyId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP AssemblyUnloadStarted(AssemblyID assemblyId) { return S_OK; };
	STDMETHODIMP AssemblyUnloadFinished(AssemblyID assemblyId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP ModuleLoadStarted(ModuleID moduleId) { return S_OK; };
	STDMETHODIMP ModuleLoadFinished(ModuleID moduleId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP ModuleUnloadStarted(ModuleID moduleId) { return S_OK; };
	STDMETHODIMP ModuleUnloadFinished(ModuleID moduleId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP ModuleAttachedToAssembly(ModuleID moduleId, AssemblyID assemblyId) { return S_OK; };
	STDMETHODIMP ClassLoadStarted(ClassID classId) { return S_OK; };
	STDMETHODIMP ClassLoadFinished(ClassID classId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP ClassUnloadStarted(ClassID classId) { return S_OK; };
	STDMETHODIMP ClassUnloadFinished(ClassID classId, HRESULT hrStatus) { return S_OK; };
	STDMETHODIMP FunctionUnloadStarted(FunctionID functionId) { return S_OK; };
	STDMETHODIMP JITCompilationStarted(FunctionID functionId, BOOL fIsSafeToBlock) { return S_OK; };
	STDMETHODIMP JITCompilationFinished(FunctionID functionId, HRESULT hrStatus, BOOL fIsSafeToBlock) { return S_OK; };
	STDMETHODIMP JITCachedFunctionSearchStarted(FunctionID functionId, BOOL * pbUseCachedFunction) { return S_OK; };
	STDMETHODIMP JITCachedFunctionSearchFinished(FunctionID functionId, COR_PRF_JIT_CACHE result) { return S_OK; };
	STDMETHODIMP JITFunctionPitched(FunctionID functionId) { return S_OK; };
	STDMETHODIMP JITInlining(FunctionID callerId, FunctionID calleeId, BOOL * pfShouldInline) { return S_OK; };
	STDMETHODIMP ThreadCreated(ThreadID threadId) { return S_OK; };
	STDMETHODIMP ThreadDestroyed(ThreadID threadId) { return S_OK; };
	STDMETHODIMP ThreadAssignedToOSThread(ThreadID managedThreadId, ULONG osThreadId) { return S_OK; };
	STDMETHODIMP RemotingClientInvocationStarted() { return S_OK; };
	STDMETHODIMP RemotingClientSendingMessage(GUID * pCookie, BOOL fIsAsync) { return S_OK; };
	STDMETHODIMP RemotingClientReceivingReply(GUID * pCookie, BOOL fIsAsync) { return S_OK; };
	STDMETHODIMP RemotingClientInvocationFinished() { return S_OK; };
	STDMETHODIMP RemotingServerReceivingMessage(GUID * pCookie, BOOL fIsAsync) { return S_OK; };
	STDMETHODIMP RemotingServerInvocationStarted() { return S_OK; };
	STDMETHODIMP RemotingServerInvocationReturned() { return S_OK; };
	STDMETHODIMP RemotingServerSendingReply(GUID * pCookie, BOOL fIsAsync) { return S_OK; };
	STDMETHODIMP UnmanagedToManagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason) { return S_OK; };
	STDMETHODIMP ManagedToUnmanagedTransition(FunctionID functionId, COR_PRF_TRANSITION_REASON reason) { return S_OK; };
	STDMETHODIMP RuntimeSuspendStarted(COR_PRF_SUSPEND_REASON suspendReason) { return S_OK; };
	STDMETHODIMP RuntimeSuspendFinished() { return S_OK; };
	STDMETHODIMP RuntimeSuspendAborted() { return S_OK; };
	STDMETHODIMP RuntimeResumeStarted() { return S_OK; };
	STDMETHODIMP RuntimeResumeFinished() { return S_OK; };
	STDMETHODIMP RuntimeThreadSuspended(ThreadID threadId) { return S_OK; };
	STDMETHODIMP RuntimeThreadResumed(ThreadID threadId) { return S_OK; };
	STDMETHODIMP MovedReferences(ULONG cMovedObjectIDRanges, ObjectID oldObjectIDRangeStart[], ObjectID newObjectIDRangeStart[], ULONG cObjectIDRangeLength[]) { return S_OK; };
	STDMETHODIMP ObjectAllocated(ObjectID objectId, ClassID classId) { return S_OK; };
	STDMETHODIMP ObjectsAllocatedByClass(ULONG cClassCount, ClassID classIds[], ULONG cObjects[]) { return S_OK; };
	STDMETHODIMP ObjectReferences(ObjectID objectId, ClassID classId, ULONG cObjectRefs, ObjectID objectRefIds[]) { return S_OK; };
	STDMETHODIMP RootReferences(ULONG cRootRefs, ObjectID rootRefIds[]) { return S_OK; }
	STDMETHODIMP ExceptionThrown(ObjectID thrownObjectId) { return S_OK; };
	STDMETHODIMP ExceptionSearchFunctionEnter(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionSearchFunctionLeave() { return S_OK; };
	STDMETHODIMP ExceptionSearchFilterEnter(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionSearchFilterLeave() { return S_OK; };
	STDMETHODIMP ExceptionSearchCatcherFound(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionOSHandlerEnter(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionOSHandlerLeave(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionUnwindFunctionEnter(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionUnwindFunctionLeave() { return S_OK; };
	STDMETHODIMP ExceptionUnwindFinallyEnter(FunctionID functionId) { return S_OK; };
	STDMETHODIMP ExceptionUnwindFinallyLeave() { return S_OK; };
	STDMETHODIMP ExceptionCatcherEnter(FunctionID functionId, ObjectID objectId) { return S_OK; };
	STDMETHODIMP ExceptionCatcherLeave() { return S_OK; };
	STDMETHODIMP COMClassicVTableCreated(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable, ULONG cSlots) { return S_OK; };
	STDMETHODIMP COMClassicVTableDestroyed(ClassID wrappedClassId, REFGUID implementedIID, void *pVTable) { return S_OK; };
	STDMETHODIMP ExceptionCLRCatcherFound(void) { return S_OK; };
	STDMETHODIMP ExceptionCLRCatcherExecute(void) { return S_OK; };

private:
	LONG                      refCount = 0;
	struct ICorProfilerInfo3* profilerInfo = NULL;
};