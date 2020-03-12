cmake_minimum_required(VERSION 3.0)
project(Alpaga)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17 ON)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES 
	sqlite3/3.29.0@bincrafters/stable
	boost/1.71.0@conan/stable
    BASIC_SETUP
)

get_filename_component(AlpagaSourcesDir ${CMAKE_CURRENT_LIST_FILE} PATH)

set(AlpagaIncludes ${AlpagaSourcesDir}/..)
set(AlpagaLibs Alpaga)

set(AlpagaSources
	${AlpagaSourcesDir}/DynamicLoader/DynamicLoader.hpp
	${AlpagaSourcesDir}/DynamicLoader/DynamicLoader.cpp

	${AlpagaSourcesDir}/SQLite/Database.cpp
	${AlpagaSourcesDir}/SQLite/Database.hpp
	${AlpagaSourcesDir}/SQLite/Statement.cpp
	${AlpagaSourcesDir}/SQLite/Statement.hpp
	${AlpagaSourcesDir}/SQLite/Transaction.cpp
	${AlpagaSourcesDir}/SQLite/Transaction.hpp

	${AlpagaSourcesDir}/Thread/ThreadPool.hpp

	${AlpagaSourcesDir}/FileWatcher/FileWatcher.hpp

	${AlpagaSourcesDir}/Utils/Str.hpp
	${AlpagaSourcesDir}/Utils/StringConvertor.hpp
)

add_library(${PROJECT_NAME} STATIC ${AlpagaSources} )
target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS_RELEASE})

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)