#pragma once

#include <shared.hpp>

// =================================
// Shared.
// =================================

void init_shared_meta(seqan3::argument_parser & parser);
void try_parsing(seqan3::argument_parser & parser);

template <typename arguments_t>
void init_shared_options(seqan3::argument_parser & parser, arguments_t & arguments)
{
    static_assert(std::same_as<arguments_t, build_arguments> || std::same_as<arguments_t, search_arguments>);

    parser.add_option(arguments.threads,
                      '\0',
                      "threads",
                      "Choose the number of threads.",
                      seqan3::option_spec::standard,
                      positive_integer_validator{});
    parser.add_option(arguments.parts,
                      '\0',
                      "parts",
                      "Splits the index in this many parts.",
                      arguments.is_socks ? seqan3::option_spec::hidden : seqan3::option_spec::standard,
                      power_of_two_validator{});
}

// =================================
// Build.
// =================================

void init_build_parser(seqan3::argument_parser & parser, build_arguments & arguments);
void run_build(seqan3::argument_parser & parser);

// =================================
// Search.
// =================================

void init_search_parser(seqan3::argument_parser & parser, search_arguments & arguments);
void run_search(seqan3::argument_parser & parser);

// =================================
// Top level.
// =================================

void init_top_level_parser(seqan3::argument_parser & parser);

// TODO: do you need validators? declare them here
