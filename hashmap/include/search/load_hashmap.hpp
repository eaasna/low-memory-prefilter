#pragma once
  
#include <cereal/types/set.hpp>
#include <cereal/types/unordered_map.hpp>
#include <chrono>

#include <seqan3/std/filesystem>
#include <seqan3/core/debug_stream.hpp>

#include <shared.hpp>

namespace hashmap
{

template <typename t>
void load_hashmap(t & hashmap, search_arguments const & arguments, double & hashmap_io_time)
{
    static uint8_t kmer_size{};
    static uint64_t bins{};

    std::ifstream is{arguments.hashmap_file, std::ios::binary};
    cereal::BinaryInputArchive iarchive{is};

    auto start = std::chrono::high_resolution_clock::now();
    
    iarchive(arguments.kmer_size);
    iarchive(arguments.bins);
    seqan3::debug_stream << "Actual nr bins: " << std::to_string(bins) << '\n';

    iarchive(hashmap);
    auto end = std::chrono::high_resolution_clock::now();

    hashmap_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

} // namespace hashmap

