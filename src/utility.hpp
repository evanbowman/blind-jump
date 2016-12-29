#pragma once
#include <array>
#include <exception>
#include <functional>
#include <iostream>
#include <mutex>

template <typename T, typename Mtx = std::mutex> struct LockedRef {
    std::reference_wrapper<T> resource;
    std::unique_lock<Mtx> lk;
};
