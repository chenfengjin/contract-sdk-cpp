.PHONY: build test

export XDEV_ROOT=$(shell pwd)
export PATH := $(shell pwd)/../../../output/:$(PATH)

build:
	./build.sh

test:
	xdev test	

build-image:
# TODO not latest
	docker build -t hub.baidubce.com/xchain/emcc:latest -f scripts/emcc.Dockerfile .