#include "shutdownSignal.hpp"

ShutdownSignal::ShutdownSignal() : msg("process terminated") {}

const char * ShutdownSignal::what() const noexcept { return msg.c_str(); }
