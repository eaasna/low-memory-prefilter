#pragma once
  
#include <chrono>
#include <future>
#include <vector>

#include <seqan3/core/debug_stream.hpp>

namespace hashmap
{

template <typename t>
inline void do_parallel(t && worker, size_t const num_records, size_t const threads, double & compute_time)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<decltype(std::async(std::launch::async, worker, size_t{}, size_t{}))> tasks;
    size_t const records_per_thread = num_records / threads;

    // TODO: remove debugging
/*
    seqan3::debug_stream << "Total records: " << std::to_string(num_records) << '\n';
    seqan3::debug_stream << "Threads: " << std::to_string(threads) << '\n';
    seqan3::debug_stream << "Records per thread: " << std::to_string(records_per_thread) << '\n';
*/    
    for (size_t i = 0; i < threads; ++i)
    {
        size_t const start = records_per_thread * i;
        size_t const end = i == (threads-1) ? num_records: records_per_thread * (i+1);
	
        // seqan3::debug_stream << "start;end " << std::to_string(start) << ";" << std::to_string(end) << '\n';
        tasks.emplace_back(std::async(std::launch::async, worker, start, end));
    }

    for (auto && task : tasks)
        task.wait();

    auto end = std::chrono::high_resolution_clock::now();
    compute_time += std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

} // namespace hashmap

