#pragma once

class Memory {
public:
	uint32_t ProcessID;
	uint64_t BaseAddress;
	HANDLE hProcess;

	Memory(const wchar_t* processName) {
		ProcessID = GetProcessID(processName);
		BaseAddress = GetBaseAddress();
		hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, ProcessID);
	}

	uint32_t GetProcessID(const wchar_t* processName) {
		HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		DWORD procID = NULL;

		if (handle == INVALID_HANDLE_VALUE)
			return procID;

		PROCESSENTRY32W entry = { 0 };
		entry.dwSize = sizeof(PROCESSENTRY32W);

		if (Process32FirstW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
			else while (Process32NextW(handle, &entry)) {
				if (!_wcsicmp(processName, entry.szExeFile)) {
					procID = entry.th32ProcessID;
				}
			}
		}

		CloseHandle(handle);
		return procID;
	}

	uint64_t GetBaseAddress() {
		uint64_t baseAddress = 0;

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
		if (snapshot == INVALID_HANDLE_VALUE) return 0;

		MODULEENTRY32 me;
		me.dwSize = sizeof(me);

		if (Module32First(snapshot, &me)) {
			baseAddress = (uint64_t)me.modBaseAddr;
		}

		CloseHandle(snapshot);
		return baseAddress;
	}

	template <typename T>
	T Read(uint64_t address) {
		T buffer{};
		ReadProcessMemory(hProcess, (LPCVOID)address, (LPVOID)&buffer, sizeof(T), NULL);
		return buffer;
	}

	template <typename T>
	void Write(uint64_t address, T value) {
		WriteProcessMemory(hProcess, (LPVOID)address, (LPCVOID)&value, sizeof(T), NULL);
	}

};

Memory* pMem;