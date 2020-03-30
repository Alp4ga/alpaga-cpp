cmake_minimum_required(VERSION 3.8)
project(tests-AlpagaLibs)

message(${CMAKE_CURRENT_SOURCE_DIR})

#################
#	GOOGLE_TEST	#
#################
# Download and unpack googletest at configure time
configure_file(Tests/CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

include_directories(
	${gtest_SOURCE_DIR}/include
	${gtest_SOURCE_DIR}
	${ALPAGA_INCLUDES}
	${CMAKE_CURRENT_BINARY_DIR}
)

#############
#	CONFIG 	#
#############
set(TEST_HOSTNAME "localhost" CACHE STRING "Hostname for mariadbpp tests")
set(TEST_PORT 3307 CACHE STRING "Port for mariadbpp tests")
set(TEST_UNIXSOCKET "" CACHE STRING "Unix socket for mariadbpp tests")
set(TEST_USERNAME "hidlo" CACHE STRING "Database username for mariadbpp tests")
set(TEST_PASSWORD "root" CACHE STRING "Database username's password for mariadbpp tests")
set(TEST_DATABASE "hidlo" CACHE STRING "Database name for mariadbpp test")

configure_file(Tests/database/mariadb/tests_config.hpp.in tests_config.hpp)

################################
# Unit Tests
################################
# Add test cpp file
add_executable(${PROJECT_NAME}
	###########
	# MARIADB #
	###########
	Tests/database/mariadb/tests_database.cpp
	Tests/database/mariadb/tests_statement.cpp
)
#############
#	C++17	#
#############
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PRIVATE ${gitStyleIncludes})
target_link_libraries(${PROJECT_NAME}
	gtest 
	gtest_main
	AlpagaLibs
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})