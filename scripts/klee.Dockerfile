FROM xuper/emcc:llvm_backend
# ------------------------------------------------------------------------------
# Use commonly used /src as working directory
WORKDIR /src

RUN sed -i s/archive.ubuntu.com/mirrors.163.com/g /etc/apt/sources.list
RUN sed -i s/security.ubuntu.com/mirrors.163.com/g /etc/apt/sources.list
RUN apt update && apt install -y clang*11
RUN apt install -y clang
RUN apt install -y file

# klee setup
RUN pip install --upgrade wllvm
ENV LLVM_COMPILER=clang
ENV CC=wllvm
ENV CXX=wllvm++
ENV PATH=/emsdk:/emsdk/upstream/emscripten:/emsdk/node/14.18.2_64bit/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
