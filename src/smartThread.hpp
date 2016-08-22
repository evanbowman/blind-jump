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
