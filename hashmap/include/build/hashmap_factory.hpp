#pragma once

#include <unordered_map>
#include <set>

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/search/views/kmer_hash.hpp>
#include <seqan3/utility/views/zip.hpp>

#include <build/call_sequential_on_bins.hpp>

namespace hashmap
{
class hashmap_factory
{
public:
    hashmap_factory() = default;
    hashmap_factory(hashmap_factory const &) = default;
    hashmap_factory(hashmap_factory &&) = default;
    hashmap_factory & operator=(hashmap_factory const &) = default;
    hashmap_factory & operator=(hashmap_factory &&) = default;
    ~hashmap_factory() = default;
    
    explicit hashmap_factory(build_arguments const & args) : arguments{std::addressof(args)} {}

    template <typename view_t = int>
    [[nodiscard]] auto operator()(view_t && hash_filter_view = 0) const
    {
        auto tmp = construct(std::move(hash_filter_view));
        return tmp;
    }


private:
    build_arguments const * const arguments{nullptr};

    template <typename view_t>
    auto construct(view_t && hash_filter_view) const
    {
	using sequence_file_t = seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::seq>>;
	
	assert(arguments != nullptr);
	
	std::unordered_map<uint32_t, std::set<uint16_t>> hm;
	
	auto hash_view = [&] ()
	{
	    return seqan3::views::kmer_hash(seqan3::shape{seqan3::ungapped{arguments->kmer_size}});
	};
	
	seqan3::debug_stream << "Processing_bin: " << '\n';
	auto worker = [&] (auto && zipped_view, auto &&)
	{
	    for (auto && [file_names, bin_number] : zipped_view)
	    {
		seqan3::debug_stream << std::to_string(bin_number) << '\n';
                for (auto && file_name : file_names)
                    for (auto && [seq] : sequence_file_t{file_name})
			// for each k-mer in a sequence
                        for (auto && value : seq | hash_view())
			{
			    // add the bin number to the list that corresponds to the k-mer hash key
			    hm[value].insert(bin_number);
	    		    // TODO: this only works if you give the paths in order of bin number
			}
	    }
	};

	call_sequential_on_bins(worker, *arguments);

	return hm;
    }
};

} // namespace hashmap
