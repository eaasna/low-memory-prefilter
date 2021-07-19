#include <seqan3/argument_parser/all.hpp> // includes all necessary headers
#include <seqan3/core/debug_stream.hpp>   // our custom output stream

void init_build_parser(seqan3::argument_parser & parser, cmd_arguments & args)
{
    parser.info.author = "Evelin Aasna";
    parser.info.short_description = "Low memory alternative to an IBF based pre-filter.";
    parser.info.version = "1.0.0";
 
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
    parser.add_option(output_file, 'o', "output", "The file for fasta output. Default: stdout");
    parser.add_flag(verbose, 'v', "verbose", "Give more detailed information here."); // example for a flag
};

void init_search_parser(seqan3::argument_parser & parser, cmd_arguments & args)
{
    parser.info.author = "Evelin Aasna";
    parser.info.short_description = "Low memory alternative to an IBF based pre-filter.";
    parser.info.version = "1.0.0";
 
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
    parser.add_option(output_file, 'o', "output", "The file for fasta output. Default: stdout");
    parser.add_flag(verbose, 'v', "verbose", "Give more detailed information here."); // example for a flag
};

void init_shared_meta(seqan3::argument_parser & parser)
{
    parser.info.app_name = "Low-memory-prefilter";
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
