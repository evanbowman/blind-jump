#pragma once
#include <exception>
#include <string>

// The shutdown process:
//  1. Player selects quit from UI menu
//  2. UI controller throws ShutdownSignal
//  3. Logic thread catches exception and exits
//
// Why I'm doing it this way:
// RAII takes care of the critical sections during stack unwinding,
// simplifies the logic of closing the app.

class ShutdownSignal : public std::exception {
    std::string msg;

public:
    ShutdownSignal();
    const char * what() const noexcept override;
    virtual ~ShutdownSignal() {}
};
