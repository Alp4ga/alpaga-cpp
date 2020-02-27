cmake_minimum_required(VERSION 3.0)
project(Alpaga)

# This file is used to compile Alpaga as a separate CMake project

include(Alpaga/Alpaga.cmake)

if (${ALPAGA_TESTS})
    include(Tests/Tests.cmake)
endif ()