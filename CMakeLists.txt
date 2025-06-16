cmake_minimum_required(VERSION 3.14)

project(OfficeGenClient LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Network)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

file(GLOB_RECURSE project_sources DESTINATION src/*)

add_executable(OfficeGenClient ${project_sources})

target_link_libraries(OfficeGenClient
    gRPC::grpc++
    gRPC::grpc

    Qt6::Widgets
    Qt6::Core
    Qt6::Network)


set(proto_gen_path ${CMAKE_BINARY_DIR}/proto)
file(MAKE_DIRECTORY ${proto_gen_path})
target_include_directories(OfficeGenClient PUBLIC ${proto_gen_path})


protobuf_generate(
    TARGET OfficeGenClient
    LANGUAGE cpp
    OUT_VAR proto_sources
    PROTOC_OUT_DIR ${proto_gen_path}
    PROTOS OfficeGenProto/office.proto
    IMPORT_DIRS ${CMAKE_SOURCE_DIR}/OfficeGenProto/
    APPEND_PATH
)

protobuf_generate(
    TARGET OfficeGenClient
    LANGUAGE grpc
    OUT_VAR proto_grpc_sources
    PLUGIN protoc-gen-grpc=/usr/bin/grpc_cpp_plugin
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PROTOC_OUT_DIR ${proto_gen_path}
    PROTOS OfficeGenProto/office.proto
    IMPORT_DIRS ${CMAKE_SOURCE_DIR}/OfficeGenProto/
    APPEND_PATH
)


