cmake_minimum_required(VERSION 3.0)
project(AlpagaLibs CXX)

#################
#	USE C++17	#
#################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17 ON)

#############
#	CONAN	#
#############
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)

#####################
#	CONAN PACKAGE	#
#####################
conan_cmake_run(REQUIRES
	boost/1.71.0@conan/stable
    BASIC_SETUP
	BUILD missing
)

set(SOURCES
	${CMAKE_CURRENT_LIST_DIR}/database/mysql/database.cpp
	${CMAKE_CURRENT_LIST_DIR}/database/mysql/database.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

#########################
#	EXTRA DEPENDENCIES	#
#########################
include(${CMAKE_CURRENT_LIST_DIR}/database/mysql/CMakeLists.txt.in)
include_directories(${PROJECT_NAME} PRIVATE
	${MYSQL_INCLUDES}
)

#########################
#	INCLUDE DIRECTORY	#
#########################
set(ALPAGA_INCLUDES ${CMAKE_CURRENT_LIST_DIR})

#############
#	LIB 	#
#############
target_link_libraries(${PROJECT_NAME} PUBLIC 
	${CONAN_LIBS}
	${MYSQL_LIB}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

#################
#	DLL WINDOWS	#
#################
if(WIN32)
	MYSQL_DLL("${CMAKE_CURRENT_LIST_DIR}/database/mysql")
endif(WIN32)