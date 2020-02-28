cmake_minimum_required(VERSION 3.0)
project(Alpaga)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17 ON)

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
)

add_library(${PROJECT_NAME} STATIC ${AlpagaSources} )
target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::sqlite3 CONAN_PKG::boost)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)