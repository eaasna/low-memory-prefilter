#pragma once

#include <shared.hpp>

namespace hashmap
{

void try_parsing(seqan3::argument_parser & parser);
void init_top_level_parser(seqan3::argument_parser & parser);
void run_build(seqan3::argument_parser & parser);
void run_search(seqan3::argument_parser & parser);

} // namespace hashmap
