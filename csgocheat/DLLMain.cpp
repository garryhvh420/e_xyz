
#include "virtuosity_main.h"
#include "hooks/c_hooks.h"
#include "hooks/idirect3ddevice9.h"
#include "menu/c_menu.h"
#include <thread>
#pragma comment(lib, "d3dx9.lib")
using namespace std::chrono_literals;

rifk_loader_info g_loader_info{};
DWORD g_image_base = 0x0;

c_rifk::c_rifk()
{
	c_menu::instance();
	c_netvar::instance();
	c_hooks::run();
}

#define ERR_TITLE ("DEBUGGING")

inline __declspec(noinline) void THROW_ERROR(const char* errorcode)
{
	MessageBox(NULL, errorcode, ERR_TITLE, MB_OK);
}


DWORD WINAPI entry(LPVOID lpThreadParameter)
{


	try
	{

		c_menu::instance();
		c_netvar::instance();
		c_hooks::run();



		while (!GetAsyncKeyState(VK_RCONTROL))
			Sleep(50);



		FreeLibraryAndExitThread(static_cast<HMODULE>(lpThreadParameter), 1);

	}
	catch (const std::exception& ex)
	{
		FreeLibraryAndExitThread(static_cast<HMODULE>(lpThreadParameter), 1);
	}

	// unreachable
	//return TRUE;


}

BOOL APIENTRY DllMain(_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);

		if (auto handle = CreateThread(nullptr, NULL, entry, hinstDLL, NULL, nullptr))
		{
			CloseHandle(handle);
		}
	}

	return TRUE;
}

