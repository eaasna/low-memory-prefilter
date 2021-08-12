# Hashmap

[![Build Status](https://github.com/seqan/app-template/workflows/App%20CI/badge.svg)](https://github.com/seqan/app-template/actions?query=branch%3Amaster+workflow%3A%22App+CI%22)

This is a tool for pre-filtering reads before read mapping. 
It uses a hash table as an alternative to IBF based methods.
This tools emphazises low memory usage not speed or precision.

## Algorithm
The hashmap build command creates a hash table where the keys are the complete set of k-mers. The value corresponding to a key is a list of all the bins that contain this k-mer. Building the hashmap is done single-threaded. The hashmap search command queries the hashmap and decides which bin each read should be mapped to based on the k-mer counting lemma. Querying the reads in the hashmap can be done multi-threaded.


## Building for end-users:

Instructions:
1. clone this repository: `git clone --recurse-submodules https://github.com/eaasna/low-memory-prefilter.git`
2. change to the repository directory `cd low-memory-prefilter`
3. create a build directory and visit it: `mkdir build && cd build`
4. run cmake: `cmake ../hashmap`
5. build the application: `make`
6. execute the app which is located at build/bin/ and display help page: `./hashmap -h`

## Building for development:

Instructions:
1. clone this repository: `git clone --recurse-submodules https://github.com/eaasna/low-memory-prefilter.git`
2. change to the repository directory `cd low-memory-prefilter`
3. create a build directory and visit it: `mkdir build && cd build`
4. run cmake: `cmake ../hashmap`
5. build the application: `make`
6. optional: build and run the tests: `make test`
7. optional: build the api documentation: `make doc`
8. execute the app which is located at build/bin/: `./hashmap`
