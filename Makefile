.PHONY: build test

export XDEV_ROOT=$(shell pwd)
export PATH := $(shell pwd)/../../../output/:$(PATH)

build:
	./build.sh

test:
	xdev test	

debug-build:
	XDEV_ROOT=`pwd`   xdev build  -o counter.wasm  example/counter.cc --compiler host -p
build-image:
	docker build  --build-arg=HTTPS_PROXY=agent.baidu.com:8118 --network host -t emcc:v1.0.2 .  -f scripts/emcc.Dockerfile 
