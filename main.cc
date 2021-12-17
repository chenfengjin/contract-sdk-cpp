//
// Created by chenfengjin on 2021/12/12.
//

#include <iostream>
#include <cstdio>
#include "dmessage.pb-c.h"
#include "xchain/contract.pb-c.h"
#include "xchain/contract.pb.h"

int main(){
    Xchain__PutRequest req;
    xchain__put_request__init(&req);
//    std::string ok("ok");
//    Xchain__SetOutputRequest  req;
//    xchain__set_output_request__init(&req);
//    Xchain__Response  resp;
//    xchain__response__init(&resp);
//
//
//    resp.body.data=(uint8_t*)ok.c_str();
//    resp.body.len = ok.size();
//    req.response = &resp;
//
//    uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
//    xchain__set_output_request__pack(&req, buffer);
//
//
//    std::string reqs((char*)buffer);
//    printf(reqs.data());
//    printf("%d",reqs.size());
    return 0;
}