#pragma once
  
#include <seqan3/core/algorithm/detail/execution_handler_sequential.hpp>
#include <seqan3/utility/views/chunk.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <shared.hpp>

namespace hashmap
{

template <typename algorithm_t>
void call_sequential_on_bins(algorithm_t && worker, build_arguments const & arguments)
{

    // TODO: kustuta kommentaar
    seqan3::debug_stream << "Bins: " << std::to_string(arguments.bins) << '\n';
    
    // It is easy to parallelize the construction of an IBF. That is not the case for constructing a hash table;
    // the low memory prefilter uses sequential execution handling, while raptor and the sliding window filter use 
    // parallelization for the build. 
    auto chunked_view = seqan3::views::zip(arguments.bin_path, std::views::iota(0u)) |
                        seqan3::views::chunk(arguments.bins);

    seqan3::detail::execution_handler_sequential executioner{};
    executioner.bulk_execute(std::move(worker), std::move(chunked_view), [](){});
}

} // namespace hashmap

