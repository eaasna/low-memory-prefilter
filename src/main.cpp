#include <argument_parsing.hpp>

#include <seqan3/argument_parser/all.hpp>
#include <seqan3/core/debug_stream.hpp>

#include "argument_parser.hpp"

int main(int argc, char ** argv)
{
   try
    {
        seqan3::argument_parser top_level_parser{"hashmap", argc, argv, seqan3::update_notifications::on, {"build", "search"}};
        
	hashmap::init_top_level_parser(top_level_parser);
        hashmap::try_parsing(top_level_parser);

        seqan3::argument_parser & sub_parser = top_level_parser.get_sub_parser();
        if (sub_parser.info.app_name == std::string_view{"hashmap-build"})
            hashmap::run_build(sub_parser, false);
        if (sub_parser.info.app_name == std::string_view{"hashmap-search"})
            hashmap::run_search(sub_parser, false);
    }
    catch (seqan3::argument_parser_error const & ext)
    {
        std::cerr << "[Parsing error] " << ext.what() << '\n';
        std::exit(-1);
    }

    return 0;
}
