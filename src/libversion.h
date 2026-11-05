///////////////////////////////////////////////////////////////////////////////
// libversion.h
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright (C) 2000-2026 Åke Hedman and contributors, The VSCP Project, 
// <akhe@vscp.org>
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

/*
  Library version information for the VSCP Helper Library.
  The format is major.minor.revision.patch. Set the revision manually to an
  unpadded decimal value from 0 to 255; the patch is the Git first-parent count.
*/



#define VSCP_HELPER_LIB_VERSION "15.3.3.273"


#define VSCP_HELPER_LIB_VERSION_MAJOR 15
#define VSCP_HELPER_LIB_VERSION_MINOR 3
#define VSCP_HELPER_LIB_VERSION_REVISION 3

#define VSCP_HELPER_LIB_VERSION_PATCH 273

#if VSCP_HELPER_LIB_VERSION_REVISION < 0 || VSCP_HELPER_LIB_VERSION_REVISION > 255
#error "VSCP_HELPER_LIB_VERSION_REVISION must be between 0 and 255"
#endif
