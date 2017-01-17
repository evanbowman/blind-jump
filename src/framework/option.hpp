//==========================================================================//
// Copyright 2016 Evan Bowman                                               //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//   http://www.apache.org/licenses/LICENSE-2.0                             //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
//==========================================================================//

#pragma once

#include <iostream>
#include <array>
#include <exception>

class null_opt_err : public std::exception {
    std::string msg;
public:
    null_opt_err() : msg("Attempt to access empty option!") {}
    inline const char * what() const noexcept override {
	return msg.c_str();
    }
    virtual ~null_opt_err() {}
};
	
template <typename T>
class option {
    std::array<uint8_t, sizeof(T)> bytes;
    bool initialized;
public:
    option() : initialized(false) {}
    option(const T && val) {
	*reinterpret_cast<T *>(bytes.data()) = val;
    }
    template <typename ...Args>
    option(Args && ...args) {
	*reinterpret_cast<T *>(bytes.data()) = T(args...);
	initialized = true;
    }
    option(const option<T> & other) {
	if (other.initialized) {
	    bytes = other.bytes;
	    initialized = true;
	} else {
	    initialized = false;
	}
    }
    option(option<T> && other) {
	if (other.initialized) {
	    bytes = std::move(other.bytes);
	    initialized = true;
	    other.initialized = false;
	} else {
	    initialized = false;
	}
    }
    ~option() {
	if (initialized) {
	    reinterpret_cast<T *>(bytes.data())->~T();
	}
    }
    operator bool() { return initialized; }
    const T & value() const {
	if (!initialized) throw null_opt_err();
	return *(T *)bytes.data();
    }
};
