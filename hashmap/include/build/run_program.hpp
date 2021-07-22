#pragma once

#include <build/hashmap_factory.hpp>
#include <build/store_hashmap.hpp>

#include <seqan3/core/debug_stream.hpp>

namespace hashmap
{

void run_program(build_arguments const & arguments)
{
    hashmap_factory generator{arguments};
    auto hashmap = generator();
 
    /* TODO: kustuta see debugging 
    for (auto x : hashmap)
    { 
        if (x.first == 0)
        {
	    seqan3::debug_stream << std::to_string(x.second[0]);
	}
    }
    */ 
    store_index(arguments.out_path, hashmap, arguments);
};

} // namespace hashmap
