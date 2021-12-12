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
    uint8_t* resp;
    size_t len;
    bool ok = syscall1(method, &req, resp, &len);
    if (!ok) {
        return false;
    }
    Xchain__CallArgs* args;
    //     确认下init 是不是会分配内存
    xchain__call_args__init(args);
    args = xchain__call_args__unpack(NULL, len, resp);
    for (int i = 0; i < args->n_args; i++) {
        //        TODO 这里可能没有终结符
        _args.insert(std::make_pair(args->args[i]->key,
                                    (char*)args->args[i]->value.data));
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
    Xchain__GetRequest req;
    xchain__get_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__get_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1("GetObject", reqs, resp, &len);
    if (!ok) {
        return false;
    };
    Xchain__GetResponse response;
    xchain__get_response__unpack(NULL, len, resp);
    value = new std::string((char*)response.value.data);
    return true;
}

bool ContextImpl::put_object(const std::string& key, const std::string& value) {
    Xchain__PutRequest req;
    xchain__put_request__init(&req);
    req.key.data = (uint8_t*)key.c_str();
    req.key.len = key.size();
    req.value.data = (uint8_t*)value.c_str();
    req.value.len = value.size();

    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__put_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    uint8_t* resp;
    size_t len;
    bool ok = syscall_raw1("PutObject", reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
}

bool ContextImpl::delete_object(const std::string& key) {
    Xchain__DeleteRequest req;
    xchain__delete_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__delete_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1("DeleteObject", reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
}

bool ContextImpl::query_tx(const std::string& txid, Transaction* tx) {
    Xchain__QueryTxRequest req;
    xchain__query_tx_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__query_tx_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1("QueryTx", reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
}

bool ContextImpl::query_block(const std::string& blockid, Block* block) {
    Xchain__QueryBlockRequest req;
    xchain__query_block_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__query_block_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    std::string method;
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1("QueryBlock", reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
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

// std::unique_ptr<Iterator> ContextImpl::new_iterator(const std::string& start,
//                                                     const std::string& limit)
//                                                     {
//     return std::unique_ptr<Iterator>(
//         new Iterator(start, limit, ITERATOR_BATCH_SIZE));
// }

Account& ContextImpl::sender() { return _account; }

const std::string& ContextImpl::transfer_amount() const {
    return "0";
    //    return _call_args.transfer_amount();
}

bool ContextImpl::call(const std::string& module, const std::string& contract,
                       const std::string& method,
                       const std::map<std::string, std::string>& args,
                       Response* xresponse) {
    Xchain__ContractCallRequest req;
    xchain__contract_call_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__contract_call_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1("ContractCall", reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
}

bool ContextImpl::cross_query(const std::string& uri,
                              const std::map<std::string, std::string>& args,
                              Response* xresponse) {
    Xchain__CrossContractQueryRequest req;
    xchain__cross_contract_query_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__cross_contract_query_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    std::string method;
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1(method, reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
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
    Xchain__EmitEventRequest req;
    xchain__emit_event_request__init(&req);
    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
    xchain__emit_event_request__pack(&req, buffer);

    std::string reqs((char*)buffer);
    std::string method;
    uint8_t* resp;
    size_t len;

    bool ok = syscall_raw1(method, reqs, resp, &len);
    if (!ok) {
        return false;
    };
    return true;
}

}  // namespace xchain
