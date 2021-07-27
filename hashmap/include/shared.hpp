#pragma once

#include <seqan3/std/filesystem>

#include <seqan3/io/sequence_file/input.hpp>

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

struct dna4_traits : seqan3::sequence_file_input_default_traits_dna
{
    using sequence_alphabet = seqan3::dna4;
};

struct build_arguments
{
    uint8_t kmer_size{10u};
    uint8_t threads{1u};

    std::vector<std::vector<std::filesystem::path>> bin_path{};
    std::filesystem::path bin_file{};
    std::filesystem::path out_path{"./"};

    uint64_t bins{64};
};

struct search_arguments
{
    uint8_t kmer_size{10u};
    uint8_t threads{1u};
    uint8_t errors{0};
    uint64_t pattern_size{};

    std::filesystem::path query_file{};
    std::filesystem::path hashmap_file{};
    std::filesystem::path out_path{"./"};
   
    bool write_time{false};

    uint64_t bins{64};
};

} // namespace hashmap
