#include "ExampleProfiler.h"

class __declspec(uuid("{DF9EDC4B-25C1-4925-A3FB-6AAEB3E2FACD}")) ProfilerCLSID;



//=============================================================
//  ClassFactory for managing instances of the profiler
//=============================================================
class ExampleProfilerClassFactory : public IClassFactory
{

public:
	ExampleProfilerClassFactory() {
		refCount = 0;
	}

	ULONG __stdcall  AddRef() {
		return InterlockedIncrement(&refCount);
	}

	ULONG __stdcall Release()
	{
		auto ret = InterlockedDecrement(&refCount);
		if (ret <= 0)
			delete(this);
		return ret;
	}

	HRESULT __stdcall QueryInterface(REFIID  riid, void ** ppInterface)
	{
		if (IID_IUnknown == riid)
			*ppInterface = static_cast<IUnknown *> (this);
		else if (IID_IClassFactory == riid)
			*ppInterface = static_cast<IClassFactory *> (this);
		else
		{
			*ppInterface = NULL;
			return (E_NOTIMPL);
		}
		reinterpret_cast<IUnknown *>(*ppInterface)->AddRef();
		return (S_OK);
	}

	HRESULT __stdcall  LockServer(BOOL bLock)
	{
		return S_OK;
	}

	HRESULT __stdcall  CreateInstance(IUnknown * pUnkOuter, REFIID riid, void** ppInterface)
	{
		if (NULL != pUnkOuter)
			return (CLASS_E_NOAGGREGATION);

		auto * pProfilerCallback = new ExampleProfiler();
		if (pProfilerCallback == NULL)
			return E_OUTOFMEMORY;
		return pProfilerCallback->QueryInterface(riid, ppInterface);
	}

private:
	long refCount;

};


//=============================================================
//  Methods exposed by the DLL
//=============================================================

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv)
{
	HRESULT hr = E_FAIL;

	if (rclsid == __uuidof(ProfilerCLSID))
	{
		auto* pClassFactory = new ExampleProfilerClassFactory;
		if (pClassFactory == NULL)
			return E_OUTOFMEMORY;
		hr = pClassFactory->QueryInterface(riid, ppv);
	}

	return (hr);
}

STDAPI DllCanUnloadNow(void)
{
	return S_OK;
}
