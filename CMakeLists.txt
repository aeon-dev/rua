# Copyright (c) 2017 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 3.2.0)
project(Rua)

# Don't allow any circular dependencies. Not even for static libraries.
set_property(GLOBAL PROPERTY GLOBAL_DEPENDS_NO_CYCLES 1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake/;${CMAKE_MODULE_PATH}")

include(CompilerFlags)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_STANDARD 14)

################################################################################

if (MSVC)
    option(AEON_ENABLE_MSVC_MP_BUILD "Use the /MP flag in Visual Studio to use multiple processes per cpp file." ON)
    if (AEON_ENABLE_MSVC_MP_BUILD)
        message (STATUS "Using Visual Studio /MP flag.")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    endif ()
endif ()

add_subdirectory(dep)
add_subdirectory(mcasm)
