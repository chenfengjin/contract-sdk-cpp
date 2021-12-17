#include "xchain/xchain.h"

struct Counter : public xchain::Contract {};

DEFINE_METHOD(Counter, initialize) {
    xchain::Context* ctx = self.context();
    // const std::string& creator = ctx->arg("creator");
    // if (creator.empty()) {
    // ctx->error("missing creator");
    // return;
    // }
    // ctx->put_object("creator", creator);
    ctx->ok("initialize succeed");
}

DEFINE_METHOD(Counter, increase) {
    xchain::Context* ctx = self.context();
    // const std::string& key = ctx->arg("key");
    // std::string value;
    // ctx->get_object(key, &value);
    // int cnt = 0;
    // cnt = atoi(value.c_str());
    // ctx->logf("get value %s -> %d", key.c_str(), cnt);
    char buf[32];
    // snprintf(buf, 32, "%d", 0);
    ctx->put_object("key1", "value1");
    // ctx->emit_event("key", key);

    // ctx->emit_event("increase", buf);

    ctx->ok("ok");
}

DEFINE_METHOD(Counter, get) {
    xchain::Context* ctx = self.context();
    // const std::string& key = ctx->arg("key");
    const std::string& key = "key";
    std::string value;
    if (ctx->get_object(key, &value)) {
        ctx->ok(value);
    } else {
        ctx->error("key not found");
    }
}

int main() {}