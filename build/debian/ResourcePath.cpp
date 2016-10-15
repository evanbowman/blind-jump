#include "../../src/ResourcePath.hpp"
#include <unistd.h>
#include <cstring>

std::string resourcePath() {
	static const size_t buffer_size = 512;
	char buffer[buffer_size];
	std::memset(buffer, 0, buffer_size);
	[[gnu::unused]]
	std::size_t bytesRead = readlink("/proc/self/exe", buffer, buffer_size);
	const std::string path(buffer);
	const std::size_t lastFwdSlash = path.find_last_of("/");
    std::string pathWithoutBinary = path.substr(0, lastFwdSlash);
	return pathWithoutBinary + "/../share/blindjump/";
}
