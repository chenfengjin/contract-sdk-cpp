#include <klee/klee.h>

#include "xchain/xchain.h"

struct KleeCase : public xchain::Contract {};

DEFINE_METHOD(KleeCase, klee_cases) {
    xchain::Context* ctx = self.context();
    std::string key;
    std::string value;
    int size = ctx->auth_require_size();
    int something = size;
    if (size == 0) {
        int *a = 0, b;
        b = *a;
    } else if (size == 1) {
        int *a = 0, b;
        b = *a;
    } else if (size == 0531003) {
        auto a = new int();
        delete (a);
        delete (a);
    } else if (size == 3) {
        int a[10];
        int b = 10;
        int c = a[b];
    } else if (size == 4) {
        int a = 2147483647;
        int b = a + 1;
    } else if (size != 0) {
        int b = size / (size - something);
    }
}
int main() { klee_cases(); }