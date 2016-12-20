//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "shutdownSignal.hpp"

ShutdownSignal::ShutdownSignal() : msg("process terminated") {}

const char * ShutdownSignal::what() const noexcept { return msg.c_str(); }
