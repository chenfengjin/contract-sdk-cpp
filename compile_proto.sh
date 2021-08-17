#!/bin/bash

set -e

cd `dirname $0`
protoc --c_out=src/xchain -I ../pb ../pb/contract.proto
