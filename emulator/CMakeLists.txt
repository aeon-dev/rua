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

set(RUA_EMULATOR
    src/bus.cpp
    src/bus.h
    src/ibus_transceiver.h
    src/icontrol_unit.h
    src/main.cpp
    src/simulated_alu.cpp
    src/simulated_alu.h
    src/simulated_register8.cpp
    src/simulated_register8.h
    src/simulated_control_unit.cpp
    src/simulated_control_unit.h
    src/module.h
    src/cpu.cpp
    src/cpu.h
)

source_group(common FILES ${RUA_EMULATOR})

add_executable(emulator ${RUA_EMULATOR})

set_target_properties(emulator PROPERTIES
    FOLDER rua
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(emulator PRIVATE src)
target_link_libraries(emulator common)

install(
    TARGETS emulator
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
