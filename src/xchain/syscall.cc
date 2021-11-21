#include "xchain/syscall.h"

#include <stdint.h>

#include "protobuf-c/protobuf-c.h"
#include "xchain/contract.pb-c.h"

extern "C" uint32_t call_method(const char* method, uint32_t method_len,
                                const char* request, uint32_t request_len);
extern "C" uint32_t fetch_response(char* response, uint32_t response_len);
extern "C" uint32_t call_method_v2(const char* method, uint32_t method_len,
                                   const char* request, uint32_t request_len,
                                   char* response, uint32_t response_len,
                                   uint32_t* success);

namespace xchain {

static bool syscall_raw(const std::string& method, const std::string& request,
                        std::string* response) {
    char buf[1024];
    uint32_t buf_len = sizeof(buf);

    uint32_t response_len = 0;
    uint32_t success = 0;

    response_len =
        call_method_v2(method.data(), uint32_t(method.size()), request.data(),
                       uint32_t(request.size()), &buf[0], buf_len, &success);
    // method has no return and no error
    if (response_len <= 0) {
        return true;
    }

    // buf can hold the response
    if (response_len <= buf_len) {
        response->assign(buf, response_len);
        return success == 1;
    }

    // slow path
    response->resize(response_len + 1, 0);
    success = fetch_response(&(*response)[0u], response_len);
    return success == 1;
}

// response should be free by caller
static bool syscall_raw1(const std::string& method, const std::string& request,
                        uint8_t * response,size_t* len) {
    char buf[1024];
    uint32_t buf_len = sizeof(buf);

    uint32_t response_len = 0;
    uint32_t success = 0;

    response_len =
        call_method_v2(method.data(), uint32_t(method.size()), request.data(),
                       uint32_t(request.size()), &buf[0], buf_len, &success);
    *len = response_len;
    // method has no return and no error
    if (response_len <= 0) {
        return true;
    }

    response = (uint8_t *)malloc(response_len+1);
    // buf can hold the response
    if (response_len <= buf_len) {
        memmove(response,buf,response_len);
        return success == 1;
    }

    // slow path
//     TODO why add one
//    response->resize(response_len + 1, 0);
//     TODO 确认为什么用char*
    success = fetch_response((char*)response, response_len);
    return success == 1;
}


bool syscall1(const std::string& method, Xchain__GetCallArgsRequest* request,
              uint8_t * response,size_t* len) {
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__get_call_args_request__pack(request, buffer);
    std::string req((char*)buffer);

    bool ok = syscall_raw1(method, req, response,len);
    if (!ok) {
        return false;
    };
    return true;
}
bool syscall(const std::string& method,
             const ::google::protobuf::MessageLite& request,
             ::google::protobuf::MessageLite* response) {
    std::string req;
    std::string rep;
    request.SerializeToString(&req);
    bool ok = syscall_raw(method, req, &rep);
    if (!ok) {
        return false;
    }
    response->ParseFromString(rep);
    return true;
}
}  // namespace xchain
