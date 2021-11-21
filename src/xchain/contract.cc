#include "xchain/context_impl.h"
#include "xchain/contract.pb-c.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "xchain/xchain.h"

namespace xchain {

static void return_response(const Response& resp) {
    // Xchain__Contract__Sdk__SetOutputRequest req;
    // Xchain__Contract__Sdk__SetOutputResponse rep;
    // req.response xchain__contract__sdk__set_output_request__init(req);

//    pb::SetOutputRequest req;
//
//    pb::SetOutputResponse rep;
//    pb::Response* r = req.mutable_response();
//    r->set_status(resp.status);
//    r->set_message(resp.message);
//    r->set_body(resp.body);
//    syscall("SetOutput", req, &rep);
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
