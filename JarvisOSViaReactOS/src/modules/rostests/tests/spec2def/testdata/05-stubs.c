/* This file is autogenerated, do not edit. */

#include <stubs.h>
#include <wine/debug.h>
#include <inttypes.h>
WINE_DECLARE_DEBUG_CHANNEL(relay);

extern int __stdcall StdcallFunction(long a0);

int __stdcall $relaytrace$StdcallFunction(long a0)
{
	int retval;
	if (TRACE_ON(relay))
		DPRINTF("testdll.xyz: StdcallFunction(0x%lx)\n", (long)a0);
	retval = StdcallFunction(a0);
	if (TRACE_ON(relay))
		DPRINTF("testdll.xyz: StdcallFunction: retval = 0x%lx\n", retval);
	return retval;
}

extern int __stdcall Stdcalli386x64();

int __stdcall $relaytrace$Stdcalli386x64()
{
	int retval;
	if (TRACE_ON(relay))
		DPRINTF("testdll.xyz: Stdcalli386x64()\n");
	retval = Stdcalli386x64();
	if (TRACE_ON(relay))
		DPRINTF("testdll.xyz: Stdcalli386x64: retval = 0x%lx\n", retval);
	return retval;
}

extern int __stdcall StdcallVersionRange(long a0, long a1, wchar_t* a2, wchar_t* a3);

int __stdcall $relaytrace$StdcallVersionRange(long a0, long a1, wchar_t* a2, wchar_t* a3)
{
	int retval;
	if (TRACE_ON(relay))
		DPRINTF("testdll.xyz: StdcallVersionRange(0x%lx,0x%lx,'%ws','%ws')\n", (long)a0, (long)a1, (wchar_t*)a2, (wchar_t*)a3);
	retval = StdcallVersionRange(a0, a1, a2, a3);
	if (TRACE_ON(relay))
		DPRINTF("testdll.xyz: StdcallVersionRange: retval = 0x%lx\n", retval);
	return retval;
}

int StubFunction()
{
	DbgPrint("WARNING: calling stub StubFunction()\n");
	__wine_spec_unimplemented_stub("testdll.xyz", __FUNCTION__);
	return 0;
}

int __stdcall StdcallSuccessStub(void* a0)
{
	DbgPrint("WARNING: calling stub StdcallSuccessStub(0x%p)\n", (void*)a0);
	return 0;
}

