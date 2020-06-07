#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>

typedef HANDLE(WINAPI* CreateToolhelp32SnapshotPrototype)(DWORD, DWORD);
typedef BOOL(WINAPI* Process32FirstPrototype)(HANDLE, LPPROCESSENTRY32);
typedef Process32FirstPrototype Process32NextPrototype;
typedef BOOL (WINAPI* CloseHandlePrototype)(HANDLE);

void* GetProcAddress(const wchar_t* dllName, const wchar_t* procName);

int main()
{
	CreateToolhelp32SnapshotPrototype CreateToolhelp32Snapshot = (CreateToolhelp32SnapshotPrototype)GetProcAddress(L"kernel32", L"CreateToolhelp32Snapshot");
	Process32FirstPrototype Process32First = (Process32FirstPrototype)GetProcAddress(L"kernel32", L"Process32FirstW");
	Process32NextPrototype Process32Next = (Process32NextPrototype)GetProcAddress(L"kernel32", L"Process32NextW");
	CloseHandlePrototype CloseHandle = (CloseHandlePrototype)GetProcAddress(L"kernel32", L"CloseHandle");


	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);


	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			std::wcout << entry.szExeFile << std::endl;
		}
	}

	CloseHandle(snapshot);
	return 0;
}
