#include "ProcessHeap_ForceFlags.h"

BOOL NtGlobalFlag()
{
	PDWORD pNtGlobalFlag = NULL, pNtGlobalFlagWoW64 = NULL;

#if defined (ENV64BIT)
	BYTE* _teb64 = (BYTE*)__readgsqword(0x30);
	DWORD64 _peb64 = *(DWORD64*)(_teb64 + 0x60);
	pNtGlobalFlag = (PDWORD)(__readgsqword(0x60) + 0xBC);

#elif defined(ENV32BIT)
	BYTE* _teb32 = (BYTE*)__readfsdword(0x18);
	DWORD _peb32 = *(DWORD*)(_teb32 + 0x30);
	pNtGlobalFlag = (PDWORD)(_peb32 + 0x68);

	if (IsWoW64())
	{
		BYTE* _teb64 = (BYTE*)__readfsdword(0x18) - 0x2000;
		DWORD64 _peb64 = *(DWORD64*)(_teb64 + 0x60);
		pNtGlobalFlagWoW64 = (PDWORD)(_peb64 + 0xBC);
	}
#endif

	bool normalDetected = pNtGlobalFlag && *pNtGlobalFlag & 0x00000070;
	bool wow64Detected = pNtGlobalFlagWoW64 && *pNtGlobalFlagWoW64 & 0x00000070;
	
	if(normalDetected || wow64Detected)
		return TRUE;
	else
		return FALSE;
}