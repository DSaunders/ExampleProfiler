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

	printf("* Profiler Attached *\n");

	return S_OK;
}