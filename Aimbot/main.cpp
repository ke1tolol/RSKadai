#include "imports.h"

int main() {
    pArduino = new Arduino(L"COM3");
    if (!pArduino->IsValid()) {
        std::cout << "[ERROR] Failed to init Arduino." << std::endl;
        getchar();
        return 1;
    }

    pMem = new Memory(L"KadaiProject.exe");

    if (!pMem->ProcessID) {
        std::cout << "[ERROR] Failed to get ProcessID." << std::endl;
        getchar();
        return 1;
    }

    if (!pMem->BaseAddress) {
        std::cout << "[ERROR] Failed to get BaseAddress." << std::endl;
        getchar();
        return 1;
    }

    if (!pMem->hProcess) {
        std::cout << "[ERROR] Failed to open process." << std::endl;
        getchar();
        return 1;
    }

    float aimsmooth;
    std::cout << "Enter smooth -> ";
    std::cin >> aimsmooth;

    while (true) {
        if (Game::AimKeyPressed()) {
            Game::Aim(aimsmooth);
        }
    }

    return 0;
}