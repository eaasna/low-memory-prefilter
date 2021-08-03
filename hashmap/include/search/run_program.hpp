#pragma once

#include <seqan3/search/views/kmer_hash.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <iomanip> // std::set_precision
#include <set>
#include <unordered_map>

#include <search/do_parallel.hpp>
#include <search/load_hashmap.hpp>
#include <search/sync_out.hpp>

namespace hashmap
{

void run_program(search_arguments const & arguments)
{
    auto hashmap = std::unordered_map<uint32_t, std::set<uint16_t>>{};

    double hashmap_io_time{0.0};
    double reads_io_time{0.0};
    double compute_time{0.0};

    auto cereal_worker = [&] ()
    {
        load_hashmap(hashmap, arguments, hashmap_io_time);
    };

	    
    auto cereal_handle = std::async(std::launch::async, cereal_worker);

    seqan3::sequence_file_input<dna4_traits, seqan3::fields<seqan3::field::id, seqan3::field::seq>> fin{arguments.query_file};
    using record_type = typename decltype(fin)::record_type;
    std::vector<record_type> records{};

    sync_out synced_out{arguments.out_path};

    size_t const kmer_lemma = arguments.pattern_size + 1u > (arguments.errors + 1u) * arguments.kmer_size ?
	arguments.pattern_size + 1u - (arguments.errors + 1u) * arguments.kmer_size : 0;

    auto worker = [&] (size_t const start, size_t const end)
    {
        std::string result_string{};
        std::vector<uint64_t> read_hashes;

        auto hash_view = seqan3::views::kmer_hash(seqan3::shape{seqan3::ungapped{arguments.kmer_size}});

        for (auto && [id, seq] : records | seqan3::views::slice(start, end))
        {
            read_hashes.clear();
            result_string.clear();
            result_string += id;
            result_string += '\t';


            read_hashes = seq | hash_view | seqan3::views::to<std::vector<uint64_t>>;
            std::vector<uint16_t> result(arguments.bins, 0);
	    seqan3::debug_stream << "vektori suurus: " << std::to_string(arguments.bins) << '\n'; 
	    for (auto hash : read_hashes)
	    {
		auto itr = hashmap.find(hash);
                if (itr != hashmap.end())
		{
		    // itr->first // this is the hash value
		    // itr->second // this is the vector of all bins that contain this kmer  
		    for (uint16_t bin : itr->second)
		    {
			// how many of the kmers in the read appear in each of the bins
			result.at(bin) += 1;
	                seqan3::debug_stream << "{" << std::to_string(result.at(bin)) << "}" << '\n';
			// ++result[bin]; hirmus segmentation fault
		    }
		}
	    }

	    size_t current_bin{0};
	    size_t const threshold = kmer_lemma;

            for (auto && count : result)
            {
                if (count >= threshold)
                {
                    result_string += std::to_string(current_bin);
                    result_string += ',';
                }
                ++current_bin;
            }
            result_string += '\n';
            synced_out.write(result_string);
        }
    };


    // each chunk is 10MB
    for (auto && chunked_records : fin | seqan3::views::chunk((1ULL<<20)*10))
    {
	// TODO: deleteee
	//seqan3::debug_stream << "chunk size: " << std::to_string((1ULL<<20)*10) << '\n';
	records.clear();
        auto start = std::chrono::high_resolution_clock::now();
        std::ranges::move(chunked_records, std::cpp20::back_inserter(records));
        auto end = std::chrono::high_resolution_clock::now();
        reads_io_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	// cereal_handle is of type std::future
	// the hashmap will be loaded asynchronously
        cereal_handle.wait();
	
	// TODO: kustuta kommentaar
        /*
	seqan3::debug_stream << "All key values in map: \n";
        for (auto const &pair: hashmap) {
            seqan3::debug_stream << std::to_string(pair.first) << '\n';
            seqan3::debug_stream << std::to_string(pair.second.size()) << '\n';
        }
	*/

        do_parallel(worker, records.size(), arguments.threads, compute_time);
    }

    if (arguments.write_time)
    {
        std::filesystem::path file_path{arguments.out_path};
        file_path += ".time";
        std::ofstream file_handle{file_path};
        file_handle << "IBF I/O\tReads I/O\tCompute\n";
        file_handle << std::fixed
                    << std::setprecision(2)
                    << hashmap_io_time << '\t'
                    << reads_io_time << '\t'
                    << compute_time;
    }
};

} // namespace hashmap
