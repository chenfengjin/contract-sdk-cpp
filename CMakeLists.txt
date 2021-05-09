cmake_minimum_required(VERSION 3.5)
project(xchain)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)

add_library(xchain STATIC
        reserved/forbidden.cc
        reserved/unified_check.cc
        src/xchain/json/json.h
        src/xchain/json/json.inc.hpp
        src/xchain/table/table.h
        src/xchain/table/table.tpl.h
        src/xchain/table/types.h
        src/xchain/trust_operators/tf.pb.cc
        src/xchain/trust_operators/tf.pb.h
        src/xchain/trust_operators/trust_operators.cc
        src/xchain/trust_operators/trust_operators.h
        src/xchain/xrc01/xrc01.cc
        src/xchain/xrc01/xrc01.h
        src/xchain/xrc01/xrc01.pb.cc
        src/xchain/xrc01/xrc01.pb.h
        src/xchain/account.cc
        src/xchain/account.h
        src/xchain/basic_iterator.cc
        src/xchain/basic_iterator.h
        src/xchain/block.cc
        src/xchain/block.h
        src/xchain/context_impl.cc
        src/xchain/context_impl.h
        src/xchain/contract.cc
        src/xchain/contract.pb.cc
        src/xchain/contract.pb.h
        src/xchain/crypto.cc
        src/xchain/crypto.h
        src/xchain/error.h
        src/xchain/safemath.h
        src/xchain/syscall.cc
        src/xchain/syscall.h
        src/xchain/transaction.cc
        src/xchain/transaction.h
        src/xchain/xchain.h)

# set_target_properties(xchain PROPERTIES PUBLIC_HEADER xchain.h)


INSTALL(
  TARGETS xchain 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib 
  COMPONENT library
)
