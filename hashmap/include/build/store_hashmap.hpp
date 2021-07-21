#pragma once

#include <unordered_map>
#include <deque>
#include <fstream>

#include <seqan3/core/concept/cereal.hpp>

#include <shared.hpp>

namespace hashmap
{

// Allow to divide the reference into a maximum of 65k bins 
static inline void store_index(std::filesystem::path const & path,
                               std::unordered_map<uint32_t, std::deque<uint16_t>> const & hashmap,
                               build_arguments const & arguments)
{
    std::ofstream os{path, std::ios::binary};
    cereal::BinaryOutputArchive oarchive{os};
    oarchive(arguments.kmer_size);
    // TODO: how to ceralise an unordered_map
    // oarchive(hashmap);
}

} //namespace hashmap
