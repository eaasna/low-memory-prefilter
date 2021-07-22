#pragma once
  
#include <seqan3/std/filesystem>
#include <fstream>
#include <mutex>

namespace hashmap
{

class sync_out
{
public:
    sync_out() = default;
    sync_out(sync_out const &) = default;
    sync_out & operator=(sync_out const &) = default;
    sync_out(sync_out &&) = default;
    sync_out & operator=(sync_out &&) = default;
    ~sync_out() = default;

    sync_out(std::filesystem::path const & path) : file{path} {}

    template <typename t>
    void write(t && data)
    {
        std::lock_guard<std::mutex> lock(write_mutex);
        file << std::forward<t>(data);
    }

private:
    std::ofstream file;
    std::mutex write_mutex;
};

} // namespace hashmap

