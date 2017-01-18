#pragma once

#include "config.h"

#include <cstring>
#include <string>
#ifdef BLINDJUMP_WINDOWS
#include <Windows.h>
#elif BLINDJUMP_MAC
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#elif BLINDJUMP_LINUX
#include <linux/limits.h>
#include <unistd.h>
#endif

std::string resourcePath();
