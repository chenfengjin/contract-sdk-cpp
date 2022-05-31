CXXFLAGS ?= -g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__ -I/usr/local/include -I/src/protobuf-3.7.1/src -I ../../klee/include -Isrc -Werror=vla -I../../src
LDFLAGS ?= -O1  -L/usr/local/lib -L /src/protobuf-3.7.1/cmake/build   -lprotobuf-lite  -lstdc++

.PHONY: all build clean

all: build

clean: 
	$(RM) -r build

klee-case.o: src/main.cc
	@mkdir -p $(dir $@)
	@echo CC $(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

build: klee-case.o

