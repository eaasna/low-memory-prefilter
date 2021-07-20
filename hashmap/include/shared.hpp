#pragma once

#include <seqan3/std/filesystem>

namespace hashmap
{

//!\brief Strong type for passing the kmer size.
struct kmer { uint8_t v; };
//!\brief Strong type for passing number of bins.
struct bins { uint64_t v; };
//!\brief Strong type for passing number of bits.
struct bits { uint64_t v; };
//!\brief Strong type for passing number of hash functions.
struct hashes { uint64_t v; };

struct build_arguments
{
    uint8_t kmer_size{10u};
    uint8_t threads{1u};

    std::filesystem::path bin_file{};
    std::filesystem::path out_path{"./"};
};

struct search_arguments
{
    uint8_t kmer_size{10u};
    uint8_t threads{1u};

    std::filesystem::path query_file{};
    std::filesystem::path hashmap_file{};
    std::filesystem::path out_path{"./"};
};

} // namespace hashmap
