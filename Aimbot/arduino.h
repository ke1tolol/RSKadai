#pragma once

class Arduino {
private:
	HANDLE hSerial;

public:
	Arduino(const wchar_t* RegistryPath) {
		hSerial = CreateFile(RegistryPath, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	}

	bool IsValid() {
		return hSerial != INVALID_HANDLE_VALUE;
	}

    std::string GetSerial() {
        if (!IsValid()) return "";

        DWORD errors;
        COMSTAT status;
        ClearCommError(hSerial, &errors, &status);

        if (status.cbInQue <= 0) return "";

        char c;
        DWORD bytesRead;
        std::string line = "";

        while (ReadFile(hSerial, &c, 1, &bytesRead, NULL) && bytesRead > 0) {
            if (c == '\n') break;
            if (c != '\r') line += c;
        }
        return line;
    }
};

Arduino* pArduino;