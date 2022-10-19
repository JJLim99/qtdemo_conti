cmake_minimum_required(VERSION 3.14)

project(smartrack_v1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

# We assume that gRPC and all its dependencies are already installed
# on this system, so they can be located by find_package().

# Find Protobuf installation
# Due to bitbake not generating protobuf-config.cmake, CONFIG option is not specified for the following find_package
set(protobuf_MODULE_COMPATIBLE TRUE)
# We don't specify a precise version because it's sourced from
# the Yocto SDK
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
   find_program(_PROTOBUF_PROTOC protoc)
else()
   set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
# We don't specify a precise version because it's sourced from
# the Yocto SDK
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
   find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
   set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Find relevant packages which are required by the projects
find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Gui Widgets REQUIRED)
find_package(GTest REQUIRED CONFIG)
include(GoogleTest)

# Proto file
get_filename_component(hw_proto "./rcu-service.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/rcu-service.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/rcu-service.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/rcu-service.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/rcu-service.grpc.pb.h")
add_custom_command(
   OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
   COMMAND ${_PROTOBUF_PROTOC}
   ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
     --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
     -I "${hw_proto_path}"
     --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
     "${hw_proto}"
   DEPENDS "${hw_proto}"
   )

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(hw_grpc_proto
   ${hw_grpc_srcs}
   ${hw_grpc_hdrs}
   ${hw_proto_srcs}
   ${hw_proto_hdrs}
   )

# Include libraries
target_link_libraries(hw_grpc_proto
   ${_REFLECTION}
   ${_GRPC_GRPCPP}
   ${_PROTOBUF_LIBPROTOBUF}
   Qt${QT_VERSION_MAJOR}::Core 
   Qt${QT_VERSION_MAJOR}::Quick
   Qt${QT_VERSION_MAJOR}::Gui
   Qt${QT_VERSION_MAJOR}::Widgets
   GTest::gtest 
   GTest::gmock 
   GTest::gmock_main
   )

# Target of the executable file
foreach(_target
   main
   )
   add_executable(${_target} "main.cpp" "iGRPCClient.h" "tMockClient.h" "tGRPCPull.h" "tGRPCPush.h" "tAteCoreCntApiClientImpl.cpp" "tAteCoreCntApiClientImpl.h")
   target_link_libraries(${_target}
      hw_grpc_proto
      ${_REFLECTION}
      ${_GRPC_GRPCPP}
      ${_PROTOBUF_LIBPROTOBUF}
      Qt${QT_VERSION_MAJOR}::Core 
      Qt${QT_VERSION_MAJOR}::Quick
      Qt${QT_VERSION_MAJOR}::Gui
      Qt${QT_VERSION_MAJOR}::Widgets
      GTest::gtest 
      GTest::gmock 
      GTest::gmock_main
      )
endforeach()
