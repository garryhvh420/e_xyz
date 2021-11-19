#include "ProcessHeap_ForceFlags.h"

#if defined (ENV64BIT)
PUINT32 GetForceFlags_x64()
{
	PINT64 pProcessHeap = NULL;
	PUINT32 pHeapForceFlags = NULL;
	if (IsWindowsVistaOrGreater()){
		pProcessHeap = (PINT64)(__readgsqword(0x60) + 0x30);
		pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x74);
	}

	else {
		pProcessHeap = (PINT64)(__readgsqword(0x60) + 0x30);
		pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x18);
	}

	return pHeapForceFlags;
}

#elif defined(ENV32BIT)
PUINT32 GetForceFlags_x86()
{
	PUINT32 pProcessHeap, pHeapForceFlags = NULL;
	if (IsWindowsVistaOrGreater())
	{
		pProcessHeap = (PUINT32)(__readfsdword(0x30) + 0x18);
		pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x44);

	}

	else {
		pProcessHeap = (PUINT32)(__readfsdword(0x30) + 0x18);
		pHeapForceFlags = (PUINT32)(*pProcessHeap + 0x10);
	}

	return pHeapForceFlags;
}
#endif

BOOL HeapForceFlags()
{
	PUINT32 pHeapForceFlags = NULL;

#if defined (ENV64BIT)
	pHeapForceFlags = GetForceFlags_x64();

#elif defined(ENV32BIT)
	pHeapForceFlags = GetForceFlags_x86();

#endif

	if (*pHeapForceFlags > 0)
		return TRUE;
	else
		return FALSE;

}