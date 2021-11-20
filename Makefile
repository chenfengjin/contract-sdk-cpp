.PHONY: build test

export XDEV_ROOT=$(shell pwd)
export PATH := $(shell pwd)/../../../output/:$(PATH)

build:
	./build.sh

test:
	xdev test	

debug-build:
	XDEV_ROOT=`pwd`   xdev build  -o counter.wasm  example/counter.cc --compiler host -p
