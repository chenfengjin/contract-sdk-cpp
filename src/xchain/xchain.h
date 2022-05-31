#ifndef XCHAIN_XCHAIN_H
#define XCHAIN_XCHAIN_H

#include <klee/klee.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "xchain/account.h"
#include "xchain/basic_iterator.h"
#include "xchain/block.h"
#include "xchain/transaction.h"

namespace xchain {

struct Response {
    int status;
    std::string message;
    std::string body;
};

class Context {
public:
    ~Context() {}
    const std::map<std::string, std::string>& args() {
        std::map<std::string, std::string> ret;
        return ret;
    }
    const std::string& arg(const std::string& name) { return ""; };
    const std::string& initiator() { return ""; };
    const std::string& caller() { return ""; };

    int auth_require_size() {
        int ret;
        klee_make_symbolic(&ret, sizeof(ret), "ret");
        return ret;
    };
    const std::string& auth_require(int idx) { return ""; };
    bool get_object(const std::string& key, std::string* value) {
        bool ret;
        // klee_make_symbolic(&ret, sizeof(ret), "ret");
        // klee_make_symbolic(value, sizeof(*value), "value");
        return ret;
    };
    bool put_object(const std::string& key, const std::string& value) {
        bool ret;
        // klee_make_symbolic(&ret, sizeof(ret), "ret");
        return ret;
    };
    bool delete_object(const std::string& key) { return true; };
    bool query_tx(const std::string& txid, Transaction* tx) { return true; };
    bool query_block(const std::string& blockid, Block* block) { return true; };
    void ok(const std::string& body) { return; }
    void error(const std::string& body) { return; }
    Response* mutable_response() {
        auto response = new Response();
        return response;
    }
    std::unique_ptr<Iterator> new_iterator(const std::string& start,
                                           const std::string& limit) {
        return std::unique_ptr<Iterator>(
            new Iterator("", "", ITERATOR_BATCH_SIZE));
    }
    Account& sender() {
        Account a;
        return a;
    }
    const std::string& transfer_amount() const { return ""; }
    bool call(const std::string& module, const std::string& contract,
              const std::string& method,
              const std::map<std::string, std::string>& args,
              Response* response) {
        return true;
    }
    bool cross_query(const std::string& uri,
                     const std::map<std::string, std::string>& args,
                     Response* response) {
        return true;
    }
    void logf(const char* fmt, ...) { return; }
    bool emit_event(const std::string& name, const std::string& body) {
        return true;
    }
};

class Contract {
public:
    Contract() {}
    ~Contract() {}
    Context* context() { return _ctx; };

private:
    Context* _ctx;
};

}  // namespace xchain

#define DEFINE_METHOD(contract_class, method_name)        \
    static void cxx_##method_name(contract_class&);       \
    extern "C" void __attribute__((used)) method_name() { \
        contract_class self;                              \
        cxx_##method_name(self);                          \
    };                                                    \
    static void cxx_##method_name(contract_class& self)

#endif
