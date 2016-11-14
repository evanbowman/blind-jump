#pragma once

#include "config.h"

#include <cstring>
#include <string>
#if WIN32 != 0
#include <Windows.h>
#elif APPLE != 0
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
#elif UNIX != 0
#include <linux/limits.h>
#include <unistd.h>
#endif

std::string resourcePath();
