#pragma once

#include <unordered_map>
#include <vector>
#include <fstream>

#include <seqan3/core/concept/cereal.hpp>

#include <shared.hpp>

namespace hashmap
{

// Allow to divide the reference into a maximum of 65k bins 
static inline void store_index(std::filesystem::path const & path,
                               std::unordered_map<uint32_t, std::vector<uint16_t>> const & hashmap,
                               build_arguments const & arguments)
{
    std::ofstream os{path, std::ios::binary};
    cereal::BinaryOutputArchive oarchive{os};
    oarchive(arguments.kmer_size);
    // TODO: is an unordered_map cerealisable?
    oarchive(hashmap);
}

} //namespace hashmap
