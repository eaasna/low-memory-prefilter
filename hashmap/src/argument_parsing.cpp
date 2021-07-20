#include <argument_parsing.hpp>
#include <search/search.hpp>
#include <build/build.hpp>
#include <shared.hpp>

#include <seqan3/argument_parser/all.hpp> // includes all necessary headers
#include <seqan3/core/debug_stream.hpp>   // our custom output stream

namespace hashmap
{

// ==========================================
// Shared arguments.
// ==========================================

void init_shared_meta(seqan3::argument_parser & parser)
{
    parser.info.app_name = "Hashmap";
    parser.info.author = "Evelin Aasna";
    parser.info.short_description = "A low memory alternative to an IBF based pre-filter.";
    parser.info.version = "1.0.0";
}

void try_parsing(seqan3::argument_parser & parser)
{
    try
    {
        parser.parse();
    }
    catch (seqan3::argument_parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        std::exit(-1);
    }
}
void init_top_level_parser(seqan3::argument_parser & parser)
{
    init_shared_meta(parser);
    parser.info.examples = {"./hashmap build --help", "./hashmap search --help"};
}

// ==========================================
// Build.
// ==========================================

void init_build_parser(seqan3::argument_parser & parser, build_arguments & arguments)
{
    parser.add_positional_option(arguments.bin_file, 
		    "File containing one file per line per bin.",
                    seqan3::input_file_validator{});
 
    parser.add_option(arguments.kmer_size,
		    '\0',
                    "kmer",
                    "Choose the kmer size.",
                    seqan3::option_spec::standard,
                    seqan3::arithmetic_range_validator{1, 13});
    //output path as option, otherwise output is printed
    parser.add_option(arguments.out_path, 
		    '\0', 
		    "output", 
		    "The hash table output file.");
}

void run_build(seqan3::argument_parser & parser)
{
    build_arguments arguments{};
    init_build_parser(parser, arguments);
    try_parsing(parser);

    hashmap_build(arguments);
}

// ==========================================
// Search.
// ==========================================

void init_search_parser(seqan3::argument_parser & parser, search_arguments & arguments)
{
    parser.add_positional_option(arguments.query_file, 
		    "File containing query reads.",
                    seqan3::input_file_validator{});
 
    parser.add_option(arguments.hashmap_file,
		    '\0',
                    "hashmap",
                    "The hash table input file.",
		    seqan3::option_spec::standard,
                    seqan3::input_file_validator{});
    parser.add_option(arguments.errors,
		    '\0',
		    "error",
		    "Choose the number of errors.",
		    seqan3::option_spec::standard,
		    positive_integer_validator{true});
    parser.add_option(arguments.out_path, 
		    '\0', 
		    "output", 
		    "The directory to create output files.");
}

void run_search(seqan3::argument_parser & parser)
{
    search_arguments arguments{};
    init_search_parser(parser, arguments);
    try_parsing(parser);

    hashmap_search(arguments);
};

} // namespace hashmap

