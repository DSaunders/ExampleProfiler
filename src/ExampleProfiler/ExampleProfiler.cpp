#pragma once

#include "ExampleProfiler.h"
#include <cstdio>

HRESULT STDMETHODCALLTYPE ExampleProfiler::InitializeForAttach(IUnknown *pICorProfilerInfoUnk, void *pvClientData, UINT cbClientData)
{
	pICorProfilerInfoUnk->QueryInterface(__uuidof(ICorProfilerInfo3), (void **)&profilerInfo);

	printf("Profiler Attached\n");

	return S_OK;
}

ExampleProfiler::ExampleProfiler()
{
	refCount = 0;
	profilerInfo = NULL;

	memset(&lock, 0, sizeof(CRITICAL_SECTION));
	InitializeCriticalSection(&lock);
}

ExampleProfiler::~ExampleProfiler()
{
	if (profilerInfo != NULL)
		profilerInfo->Release();
	
	DeleteCriticalSection(&lock);
}