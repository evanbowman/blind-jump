#pragma once
#include <array>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>

template <typename T, typename Mtx = std::mutex> struct LockedRef {
    LockedRef(T & _resource, std::unique_lock<Mtx> && _lk)
        : resource(_resource), lk(std::forward<std::unique_lock<Mtx>>(_lk)) {}
    std::reference_wrapper<T> resource;

private:
    std::unique_lock<Mtx> lk;
};
