// vscphelperdll.h : main header file for the VSCP helper dll DLL
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright (c) 2000-2024 Ake Hedman, the VSCP Project <info@grodansparadis.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


/*!
	\file "VSCP helper dll.h"
	\mainpage VSCP helper dll.h
	\brief VSCP helper dll with the tools for VSCP program development.
	\details This is the documentation for the VSCP helper dll. This file includes
	most of the stuff that is needed by a programmer to interface CANAL drivers and
	the talk to a VSCP daemon remotly over tcp/ip. All helper functionality and all
	communication functionality is included in this dynamically loadable library.
	Also ready to work with threads for receiving and transmitting events.
	\author Ake Hedman <akhe@grodansparadis.com>, the VSCP Project, Sweden

*/

#pragma once

#include "resource.h"		// main symbols

/*!
        Add a driver object

        @parm plog Object to add
        @return handle or 0 for error
*/
long
addDriverObject(VscpRemoteTcpIf* pvscpif);

/*!
        Get a driver object from its handle

        @param handle for object
        @return pointer to object or NULL if invalid
                        handle.
*/
VscpRemoteTcpIf*
getDriverObject(long handle);

/*!
        Remove a driver object
        @param handle for object.
*/
void
removeDriverObject(long handle);
