#pragma once

#include <cereal/types/set.hpp>
#include <cereal/types/unordered_map.hpp>

#include <fstream>
#include <set>
#include <unordered_map>

#include <seqan3/core/concept/cereal.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <shared.hpp>

namespace hashmap
{

// Allow to divide the reference into a maximum of 65k bins 
static inline void store_index(std::filesystem::path const & path,
                               std::unordered_map<uint32_t, std::set<uint16_t>> const & hashmap,
                               build_arguments const & arguments)
{
    std::ofstream os{path, std::ios::binary};
    cereal::BinaryOutputArchive oarchive{os};
    
    oarchive(arguments.kmer_size);
    oarchive(arguments.bins);
    
    // TODO: kustuta kommentaar
    /*
    seqan3::debug_stream << "All key values in map: \n";
    for (auto const &pair: hashmap) {
        seqan3::debug_stream << std::to_string(pair.first) << '\n';
        seqan3::debug_stream << std::to_string(pair.second.size()) << '\n';
    }
    */
    
    oarchive(hashmap);
}

} //namespace hashmap
