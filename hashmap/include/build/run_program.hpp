#pragma once

#include <build/hashmap_factory.hpp>
#include <build/store_hashmap.hpp>

namespace hashmap
{

void run_program(build_arguments const & arguments)
{
    // TODO: 
    // generate the hash table
    // store it
   
    /*	
    hashmap_factory generator(arguments);
    auto hm = std::move(generator.hm);

    */

    hashmap_factory generator{arguments};
    auto hashmap = generator();

    //store_index(arguments.out_path, hm, arguments);
};

} // namespace hashmap
