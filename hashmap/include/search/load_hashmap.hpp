#pragma once
  
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/deque.hpp>
#include <chrono>

#include <seqan3/std/filesystem>

#include <shared.hpp>

namespace hashmap
{

template <typename t>
void load_hashmap(t & hashmap, search_arguments const & arguments, double & hashmap_io_time)
{
    static uint8_t kmer_size{};

    std::ifstream is{arguments.hashmap_file, std::ios::binary};
    cereal::BinaryInputArchive iarchive{is};

    auto start = std::chrono::high_resolution_clock::now();
    iarchive(kmer_size);
    iarchive(hashmap);
    auto end = std::chrono::high_resolution_clock::now();

    hashmap_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

} // namespace hashmap

