#include "xchain/context_impl.h"
#include "xchain/contract.pb-c.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "xchain/xchain.h"

namespace xchain {

static void return_response(const Response& resp) {
    Xchain__SetOutputRequest req;
    xchain__set_output_request__init(&req);

    Xchain__Response response;
    xchain__response__init(&response);
    response.body.data = (uint8_t*)resp.body.c_str();
    response.body.len = resp.body.length();

    req.response->status = resp.status;
    req.response = &response;

    uint8_t* buffer1 = (uint8_t*)malloc(sizeof(uint8_t) * 2048);

    xchain__set_output_request__pack(&req, buffer1);

    std::string reqs(((char*)buffer1));
    uint8_t* resp1;
    size_t len;

    syscall_raw1("SetOutput", reqs, resp1, &len);
}

Contract::Contract() {
    ContextImpl* ctximpl = new (ContextImpl);
    ctximpl->init();
    _ctx = ctximpl;
}

Contract::~Contract() {
    return_response(*_ctx->mutable_response());
    delete (_ctx);
}

}  // namespace xchain
