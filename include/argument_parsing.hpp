#pragma once

#include <shared.hpp>

void init_build_parser(seqan3::argument_parser & parser, build_arguments & arguments);
void run_build(seqan3::argument_parser & parser, bool const is_socks);

void init_search_parser(seqan3::argument_parser & parser, search_arguments & arguments);
void run_search(seqan3::argument_parser & parser, bool const is_socks);

void init_top_level_parser(seqan3::argument_parser & parser);

// TODO: do you need validators? declare them here
