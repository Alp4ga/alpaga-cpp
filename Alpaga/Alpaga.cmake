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
	CMAKE_TARGETS
)

set(SOURCES
	###########
	# MARIADB #
	###########
	${CMAKE_CURRENT_LIST_DIR}/database/mariadb/Database.cpp
	${CMAKE_CURRENT_LIST_DIR}/database/mariadb/Database.hpp
	${CMAKE_CURRENT_LIST_DIR}/database/mariadb/Statement.cpp
	${CMAKE_CURRENT_LIST_DIR}/database/mariadb/Statement.hpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

#################################
#	EXTRA DEPENDENCIES MARIADB	#
#################################
if(WIN32)
	link_directories(${CMAKE_CURRENT_LIST_DIR}/database/mariadb/mariadb-connector/windows)
elseif(UNIX)
	link_directories(${CMAKE_CURRENT_LIST_DIR}/database/mariadb/mariadb-connector/unix)
endif()
set(MARIADB_LIB libmariadb mariadbclient)
include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/database/mariadb/mariadb-connector/include)

#########################
#	INCLUDE DIRECTORY	#
#########################
set(ALPAGA_INCLUDES ${CMAKE_CURRENT_LIST_DIR})

#############
#	LIB 	#
#############
target_link_libraries(${PROJECT_NAME} PUBLIC 
	${MARIADB_LIB}
	CONAN_PKG::boost
)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

#################
#	DLL WINDOWS	#
#################
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_LIST_DIR}/database/mariadb/mariadb-connector/windows/libmariadb.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif(WIN32)