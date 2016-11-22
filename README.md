Request Parser
==============

A demo for fuzz testing.

To build:

    mkdir ../build && cd ../build
    CC=$(which clang) CXX=$(which clang++) cmake -G Ninja ../request_parser
    ninja
    ./tests

To run the fuzzer:

    cd ../build
    mkdir CORPUS
    ./fuzzer CORPUS
