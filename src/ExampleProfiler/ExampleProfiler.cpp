#include "ExampleProfiler.h"
#include <cstdio>

ExampleProfiler::ExampleProfiler()
{
}

ExampleProfiler::~ExampleProfiler()
{
	if (profilerInfo != NULL)
		profilerInfo->Release();
}

HRESULT STDMETHODCALLTYPE ExampleProfiler::InitializeForAttach(IUnknown *pICorProfilerInfoUnk, void *pvClientData, UINT cbClientData)
{
	pICorProfilerInfoUnk->QueryInterface(__uuidof(ICorProfilerInfo3), (void **)&profilerInfo);

	// Specify that we want to receive all events from the CLR
	profilerInfo->SetEventMask(COR_PRF_ALL);
	
	return S_OK;
}

/* 
	This is all that is required to implement a callback from the CLR.
	(note that the implementation of this method in ExampleProfiler.h has been removed)
*/
STDMETHODIMP ExampleProfiler::GarbageCollectionFinished(void) 
{
	printf("Profiler: Garbage Collection\n");

	return S_OK;
}