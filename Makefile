.PHONY: build test

export XDEV_ROOT=$(shell pwd)
export PATH := $(shell pwd)/../../../output/:$(PATH)

build:
	./build.sh

test:
	xdev test	

upgrade:
	XDEV_CC_IMAGE=emcc:v1.0.2 xdev build  -o counter.wasm example/counter.cc
	cd ~/baidu/xuperchain/output&& bin/xchain-cli wasm upgrade --account XC1111111111111111@xuper --cname counter --fee 5000000 ~/baidu/contract-sdk-cpp/counter.wasm
invoke:
	cd ~/baidu/xuperchain/output && bin/xchain-cli wasm invoke  --fee 100   --method  increase -a '{"key":"xchain"}'  counter  --fee 999999

build-image:
	docker build  --build-arg=HTTPS_PROXY=agent.baidu.com:8118 --network host -t emcc:v1.0.2 .  -f scripts/emcc.Dockerfile 
