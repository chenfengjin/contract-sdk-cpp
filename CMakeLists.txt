cmake_minimum_required(VERSION 3.16)
project(contract_sdk_cpp)

set(CMAKE_CXX_STANDARD 14)
add_link_options(-lprotobuf)
link_directories(/Users/chenfengjin/baidu/protobuf-3.7.1/cmake/build)
include_directories(src)
include_directories(/Users/chenfengjin/baidu/protobuf-3.7.1/src)
add_executable(contract_sdk_cpp
        main.cc
        dmessage.pb-c.c
        dmessage.pb-c.h
        src/protobuf-c/protobuf-c.c
        src/protobuf-c/protobuf-c.h
        src/protobuf-c/protobuf-c.pb.cc
        src/protobuf-c/protobuf-c.pb.h
        src/xchain/contract.pb.h
        src/xchain/contract.pb.cc
        src/xchain/contract.pb-c.c
        src/xchain/contract.pb-c.h
        )
