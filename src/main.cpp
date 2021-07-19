#include <sstream>

#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>

#include "argument_parser.hpp"

int main(int argc, char ** argv)
{
    seqan3::argument_parser myparser{"Low-memory-prefilter", argc, argv};        // initialise myparser
    cmd_arguments args{};
 
    initialise_argument_parser(myparser, args);

    try
    {
         parser.parse();                                                  // trigger command line parsing
    }
    catch (seqan3::argument_parser_error const & ext)                     // catch user errors
    {
        seqan3::debug_stream << "Parsing error. " << ext.what() << "\n"; // give error message
        return -1;
    }

    // convert_fastq(fastq_file, output_file); // Call fastq to fasta converter

    if (verbose) // if flag is set
        seqan3::debug_stream << "Conversion was a success. Congrats!\n";



    return 0;
}
