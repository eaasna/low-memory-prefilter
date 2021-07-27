#pragma once

#include <build/hashmap_factory.hpp>
#include <build/store_hashmap.hpp>

namespace hashmap
{

void run_program(build_arguments const & arguments)
{
    hashmap_factory generator{arguments};
    auto hashmap = generator();
    store_index(arguments.out_path, hashmap, arguments);
};

} // namespace hashmap
