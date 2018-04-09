#...............................................................................

project (pipe_throughput_test)

cmake_minimum_required (VERSION 3.3)

include (axl_cmake.cmake NO_POLICY_SCOPE)

#...............................................................................

include_directories (${AXL_INC_DIR})
link_directories (${AXL_LIB_DIR})

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

add_executable (
	pipe_client
	client.cpp
	config.h
	pch.h
	pch_client.cpp
	)

axl_set_pch (
	pipe_client
	pch.h
	pch_client.cpp
	)

target_link_libraries (
	pipe_client
	axl_io
	axl_core
	)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

add_executable (
	pipe_server
	server.cpp
	config.h
	pch.h
	pch_server.cpp
	)

axl_set_pch (
	pipe_server
	pch.h
	pch_server.cpp
	)

target_link_libraries (
	pipe_server
	axl_io
	axl_core
	)

#...............................................................................
