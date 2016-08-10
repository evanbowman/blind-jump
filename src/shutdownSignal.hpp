//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

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
