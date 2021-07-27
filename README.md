# Hashmap

[![Build Status](https://github.com/seqan/app-template/workflows/App%20CI/badge.svg)](https://github.com/seqan/app-template/actions?query=branch%3Amaster+workflow%3A%22App+CI%22)

This is a tool for pre-filtering reads before read mapping. 
It uses an hash table as an alternative to the usual IBF based methods.
This tools emphazises low memory usage not speed or precision.

Instructions:
1. clone this repository: `git clone --recurse-submodules https://github.com/eaasna/low-memory-prefilter.git`
3. create a build directory and visit it: `mkdir build && cd build`
4. run cmake: `cmake ../hashmap`
5. build the application: `make`
6. optional: build and run the tests: `make test`
7. optional: build the api documentation: `make doc`
8. execute the app which is located at build/bin/: `./hashmap`

Building the hashmap is done single-threaded. Querying the reads in the hashmap can be done multi-threaded.
