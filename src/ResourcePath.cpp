#include "ResourcePath.hpp"

#include <iostream>

#ifdef BLINDJUMP_WINDOWS
std::string resourcePath() {
    HMODULE hModule = GetModuleHandleW(nullptr);
    char buffer[MAX_PATH];
    GetModuleFileName(hModule, buffer, MAX_PATH);
    const std::string path(buffer);
    const std::size_t lastFwdSlash = path.find_last_of('\\');
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash + 1);
#ifdef _DEBUG
    return pathWithoutBinary + "..\\..\\res\\";
#else
    return pathWithoutBinary + "res\\";
#endif
}
#elif BLINDJUMP_MAC
std::string resourcePath() {
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    _NSGetExecutablePath(buffer, &size);
    const std::string path(buffer);
    const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash + 1);
    return pathWithoutBinary + "../Resources/";
}
#elif BLINDJUMP_LINUX
std::string resourcePath() {
    char buffer[PATH_MAX];
    [[gnu::unused]] const std::size_t bytesRead =
        readlink("/proc/self/exe", buffer, sizeof(buffer));
    const std::string path(buffer);
    const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash + 1);
    return pathWithoutBinary + "../res/";
}
#endif
