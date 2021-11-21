#include "xchain/context_impl.h"

#include <stdarg.h>
#include <stdio.h>

#include "xchain/contract.pb-c.h"
#include "xchain/syscall.h"

namespace xchain {

ContextImpl::ContextImpl() {}

ContextImpl::~ContextImpl() {}

const std::string& ContextImpl::method() {
    return "";
//    return _call_args.method();
}

bool ContextImpl::init() {
    // pb::GetCallArgsRequest req;
    Xchain__GetCallArgsRequest req;
    xchain__get_call_args_request__init(&req);
    std::string method = "GetCallArgs";
    uint8_t * resp;
    size_t len;
    bool ok = syscall1(method, &req, resp,&len);
    if (!ok) {
        return false;
    }
    Xchain__CallArgs*  args;
//     确认下init 是不是会分配内存
    xchain__call_args__init(args);
    args =  xchain__call_args__unpack(NULL,len,resp);
    for(int i = 0;i<args->n_args;i++){
//        TODO 这里可能没有终结符
        _args.insert(std::make_pair(args->args[i]->key, (char*)args->args[i]->value.data));
    }
    _resp.status = 200;
//    _account = Account(_call_args.initiator());

    return true;
}

const std::map<std::string, std::string>& ContextImpl::args() const {
    return _args;
}

const std::string& ContextImpl::arg(const std::string& name) const {
    auto it = _args.find(name);
    if (it != _args.end()) {
        return it->second;
    }
    return kUnknownKey;
}

const std::string& ContextImpl::initiator() const {
//    return "";
//    return _call_args.initiator();
}

int ContextImpl::auth_require_size() const {
    return 0;
//    return _call_args.auth_require_size();
}

const std::string& ContextImpl::auth_require(int idx) const {
    return "";
//    return _call_args.auth_require(idx);
}

bool ContextImpl::get_object(const std::string& key, std::string* value) {
    return true;
//    pb::GetRequest req;
//    pb::GetResponse rep;
//    req.set_key(key);
//    bool ok = syscall("GetObject", req, &rep);
//    if (!ok) {
//        return false;
//    }
//    *value = rep.value();
//    return true;
}

bool ContextImpl::put_object(const std::string& key, const std::string& value) {
    return true;
//    pb::PutRequest req;
//    pb::PutResponse rep;
//    req.set_key(key);
//    req.set_value(value);
//    bool ok = syscall("PutObject", req, &rep);
//    if (!ok) {
//        return false;
//    }
//    return true;
}

bool ContextImpl::delete_object(const std::string& key) {
    return true;
//    pb::DeleteRequest req;
//    pb::DeleteResponse rep;
//    req.set_key(key);
//    bool ok = syscall("DeleteObject", req, &rep);
//    if (!ok) {
//        return false;
//    }
//    return true;
}

bool ContextImpl::query_tx(const std::string& txid, Transaction* tx) {
    return true;
//    pb::QueryTxRequest req;
//    pb::QueryTxResponse rep;
//
//    req.set_txid(txid);
//    bool ok = syscall("QueryTx", req, &rep);
//    if (!ok) {
//        return false;
//    }
//
//    tx->init(rep.tx());
//
//    return true;
}

bool ContextImpl::query_block(const std::string& blockid, Block* block) {
    return true;
//    pb::QueryBlockRequest req;
//    pb::QueryBlockResponse rep;
//
//    req.set_blockid(blockid);
//    bool ok = syscall("QueryBlock", req, &rep);
//    if (!ok) {
//        return false;
//    }
//
//    block->init(rep.block());

//    return true;
}

void ContextImpl::ok(const std::string& body) {
    _resp.status = 200;
    _resp.body = body;
}

void ContextImpl::error(const std::string& body) {
    _resp.status = 500;
    _resp.message = body;
}

Response* ContextImpl::mutable_response() { return &_resp; }

const Response& ContextImpl::get_response() { return _resp; }

std::unique_ptr<Iterator> ContextImpl::new_iterator(const std::string& start,
                                                    const std::string& limit) {
    return std::unique_ptr<Iterator>(
        new Iterator(start, limit, ITERATOR_BATCH_SIZE));
}

Account& ContextImpl::sender() { return _account; }

const std::string& ContextImpl::transfer_amount() const {
    return "0";
//    return _call_args.transfer_amount();
}

bool ContextImpl::call(const std::string& module, const std::string& contract,
                       const std::string& method,
                       const std::map<std::string, std::string>& args,
                       Response* xresponse) {
    return true;
//    pb::ContractCallRequest request;
//    pb::ContractCallResponse response;
//    request.set_module(module);
//    request.set_contract(contract);
//    request.set_method(method);
//    for (auto it = args.begin(); it != args.end(); it++) {
//        auto arg = request.add_args();
//        arg->set_key(it->first);
//        arg->set_value(it->second);
//    }
//    bool ok = syscall("ContractCall", request, &response);
//    if (!ok) {
//        return false;
//    }
//    xresponse->status = response.response().status();
//    xresponse->message = response.response().message();
//    xresponse->body = response.response().body();
//    return true;
}

bool ContextImpl::cross_query(const std::string& uri,
                              const std::map<std::string, std::string>& args,
                              Response* xresponse) {
    return true;
//    pb::CrossContractQueryRequest request;
//    pb::CrossContractQueryResponse response;
//    request.set_uri(uri);
//    for (auto it = args.begin(); it != args.end(); it++) {
//        auto arg = request.add_args();
//        arg->set_key(it->first);
//        arg->set_value(it->second);
//    }
//    bool ok = syscall("CrossContractQuery", request, &response);
//    if (!ok) {
//        return false;
//    }
//    xresponse->status = response.response().status();
//    xresponse->message = response.response().message();
//    xresponse->body = response.response().body();
    return true;
}

void ContextImpl::logf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    putchar('\n');
}

bool ContextImpl::emit_event(const std::string& name, const std::string& body) {
    return true;
//    pb::EmitEventRequest request;
//    pb::EmitEventResponse response;
//    request.set_name(name);
//    request.set_body(body);
//    bool ok = syscall("EmitEvent", request, &response);
//    if (!ok) {
//        return false;
//    }
//    return true;
}

}  // namespace xchain
