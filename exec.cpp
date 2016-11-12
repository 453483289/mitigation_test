#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "console_color.hpp"

int __cdecl wmain(int argc, PWSTR argv[])
{
	if (argc < 2)
		return EXIT_FAILURE;
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
	STARTUPINFOW si = { sizeof si };
	PROCESS_INFORMATION pi;
	if (!CreateProcessW(nullptr, argv[1], nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
	{
		printf_red("!CreateProcess:%x\n", GetLastError());
		return EXIT_FAILURE;
	}
	if (WaitForSingleObject(pi.hProcess, INFINITE) != WAIT_OBJECT_0)
	{
		printf_red("!WaitForSingleObject:%x\n", GetLastError());
		return EXIT_FAILURE;
	}
	ULONG exit_code;
	if (!GetExitCodeProcess(pi.hProcess, &exit_code))
	{
		printf_red("!GetExitCodeProcess:%x\n", GetLastError());
		return EXIT_FAILURE;
	}
	if (exit_code != EXIT_SUCCESS)
		printf_red("Process ABEND:%x\n", exit_code);
	return exit_code;
}