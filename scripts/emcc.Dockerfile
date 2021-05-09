FROM trzeci/emscripten:1.38.48
RUN curl -LO https://github.com/protocolbuffers/protobuf/releases/download/v3.7.1/protobuf-cpp-3.7.1.tar.gz
RUN tar xf protobuf-cpp-3.7.1.tar.gz
RUN cd protobuf-3.7.1/ && emconfigure ./configure && emmake make -j 4 && emmake make install
# install library
COPY . . 
RUN mkdir build && cd build && cmake ..
RUN cd build && emmake make && emmake make install 