#include <Windows.h>
#include <cstring>
#include <string>

#include "../../ResourcePath.hpp"

std::string ResourcePath() {
    HMODULE hModule = GetModuleHandleW(nullptr);
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(hModule, buffer, MAX_PATH);
    const std::string path(buffer);
    const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash);
    return pathWithoutBinary + "../Resources/";
}
