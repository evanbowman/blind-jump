#pragma once

#include "config.h"

#include <cstring>
#include <string>
#if WIN32 != 0
#include <Windows.h>
#elif APPLE != 0
#include <sys/syslimits.h>
#include <mach-o/dyld.h>
#elif UNIX != 0
#include <linux/limits.h>
#include <unistd.h>
#endif

std::string resourcePath();
