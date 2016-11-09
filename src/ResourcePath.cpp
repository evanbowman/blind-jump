#include "ResourcePath.hpp"

#include <iostream>

#if WIN32 != 0
std::string resourcePath() {
    HMODULE hModule = GetModuleHandleW(nullptr);
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(hModule, buffer, MAX_PATH);
    const std::string path(buffer);
    // TODO: untested! Path may use backslashes since it's Windows...
    const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash + 1);
    // TODO: where to store resources?
}
#elif APPLE != 0
std::string resourcePath() {
    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);
    _NSGetExecutablePath(buffer, &size);
    const std::string path(buffer);
    const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash + 1);
    return pathWithoutBinary + "../Resources/";
}
#elif UNIX != 0
std::string resourcePath() {
    char buffer[PATH_MAX];
    [[gnu::unused]]
    const std::size_t bytesRead =
        readlink("/proc/self/exe", buffer, sizeof(buffer));
    const std::string path(buffer);
    const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash + 1);
    return pathWithoutBinary + "/../share/blindjump/";
}
#endif
