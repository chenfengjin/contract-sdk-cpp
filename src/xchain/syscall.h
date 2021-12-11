#ifndef XCHAIN_SYSCALL_H
#define XCHAIN_SYSCALL_H

#include <google/protobuf/message_lite.h>
#include <protobuf-c/protobuf-c.h>
#include <stdint.h>
#include <xchain/contract.pb-c.h>

#include <string>

namespace xchain {

bool syscall(const std::string& method,
             const ::google::protobuf::MessageLite& request,
             ::google::protobuf::MessageLite* response);
bool syscall1(const std::string& method, Xchain__GetCallArgsRequest* request,
              uint8_t* response, size_t* size);
}  // namespace xchain
static bool syscall_raw1(const std::string& method, const std::string& request,
                         uint8_t* response, size_t* len);
// namespace xchain
#endif
