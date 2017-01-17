#pragma once
#include <thread>

//==========================================================================//
// A simple RAII thread class. It does not attempt to replicate the entire  //
// std::thread interface, instead providing access to the underlying data   //
// by calling SmartThread::get(). It can be constructed the same way as an  //
// std::thread, or by moving in an existing std::thread object.             //
//==========================================================================//

class SmartThread {
    std::thread thread;
public:
    template<typename Function, typename ...Args>
    explicit SmartThread(Function && f, Args && ...args) :
	thread(std::forward<Function>(f), std::forward<Args>(args)...) {}
    SmartThread(std::thread && _thread) : thread(std::move(_thread)) {}
    SmartThread(const SmartThread &) = delete;
    SmartThread(SmartThread && other) { thread = std::move(other.thread); }
    SmartThread & operator=(SmartThread &) = delete;
    SmartThread & operator=(SmartThread && other) {
	thread = std::move(other.thread);
	return *this;
    }
    const std::thread & get() const { return thread; }
    std::thread && release() {
	return std::move(thread);
    }
    ~SmartThread() { if (thread.joinable()) thread.join(); }
};
