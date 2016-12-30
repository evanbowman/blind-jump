#pragma once
#include <array>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

template <typename T, typename Mtx = std::mutex> struct LockedRef {
    LockedRef(T & _resource, std::unique_lock<Mtx> && _lk)
        : resource(_resource), lk(std::forward<std::unique_lock<Mtx>>(_lk)) {}
    std::reference_wrapper<T> resource;

private:
    std::unique_lock<Mtx> lk;
};

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
    std::thread & get() { return thread; }
    std::thread && release() {
	return std::move(thread);
    }
    ~SmartThread() { if (thread.joinable()) thread.join(); }
};
