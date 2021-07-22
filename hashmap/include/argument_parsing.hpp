#pragma once

#include <shared.hpp>

#include <seqan3/argument_parser/all.hpp>
#include <seqan3/io/sequence_file/input.hpp>

namespace hashmap
{

// =================================
// Validators from raptor.
// =================================

class positive_integer_validator
{
public:
    using option_value_type = size_t;

    positive_integer_validator() = default;
    positive_integer_validator(positive_integer_validator const &) = default;
    positive_integer_validator & operator=(positive_integer_validator const &) = default;
    positive_integer_validator(positive_integer_validator &&) = default;
    positive_integer_validator & operator=(positive_integer_validator &&) = default;
    ~positive_integer_validator() = default;

    explicit positive_integer_validator(bool const is_zero_positive_) : is_zero_positive{is_zero_positive_} {}

    void operator()(option_value_type const & val) const
    {
        if (!is_zero_positive && !val)
            throw seqan3::validation_error{"The value must be a positive integer."};
    }

    std::string get_help_page_message () const
    {
        if (is_zero_positive)
            return "Value must be a positive integer or 0.";
        else
            return "Value must be a positive integer.";
    }

private:
    bool is_zero_positive{false};
};

class bin_validator
{
public:
    using option_value_type = std::vector<std::filesystem::path>;

    bin_validator() = default;
    bin_validator(bin_validator const &) = default;
    bin_validator & operator=(bin_validator const &) = default;
    bin_validator(bin_validator &&) = default;
    bin_validator & operator=(bin_validator &&) = default;
    ~bin_validator() = default;

    void operator() (option_value_type const & values) const
    {
        if (values.empty())
            throw seqan3::validation_error{"The list of input files cannot be empty."};

        for (auto && value : values)
        {
            try
            {
                sequence_file_validator(value);
            }
            catch (seqan3::validation_error const & exception)
            {
                if (values.size() == 1u)
                {
                    std::ifstream list_of_files{value};
                    std::string line;
                    while (std::getline(list_of_files, line))
                    {
                        if (!line.empty())
                        {
                            std::filesystem::path bin_path{line};
                            sequence_file_validator(bin_path);
                        }
                    }
                }
                else
                    throw exception;
            }
        }
    }

    std::string get_help_page_message() const
    {
        return seqan3::detail::to_string("The input file must exist and read permissions must be granted. Valid file "
                                         "extensions for bin files are: [minimiser], or ", sequence_extensions,
                                         #if defined(SEQAN3_HAS_BZIP2) || defined(SEQAN3_HAS_ZLIB)
                                         " possibly followed by: ", compression_extensions, ". ",
                                         #else
                                         ". ",
                                         #endif
                                         "All other extensions will be assumed to contain one line per path to a bin.");
    }

private:
    std::vector<std::string> sequence_extensions{seqan3::detail::valid_file_extensions<typename seqan3::sequence_file_input<>::valid_formats>()};
    std::vector<std::string> compression_extensions{[&] ()
                             {
                                 std::vector<std::string> result;
                                 #ifdef SEQAN3_HAS_BZIP2
                                     result.push_back("bz2");
                                 #endif
                                 #ifdef SEQAN3_HAS_ZLIB
                                     result.push_back("gz");
                                     result.push_back("bgzf");
                                 #endif
                                 return result;
                             }()};
    std::vector<std::string> combined_extensions{[&] ()
                             {
                                 if (compression_extensions.empty())
                                    return sequence_extensions;
                                 std::vector<std::string> result;
                                 for (auto && sequence_extension : sequence_extensions)
                                 {
                                     result.push_back(sequence_extension);
                                     for (auto && compression_extension : compression_extensions)
                                         result.push_back(sequence_extension + std::string{'.'} + compression_extension);
                                 }
                                return result;
                             }()};
public:
    seqan3::input_file_validator<> sequence_file_validator{{combined_extensions}};
};

// =================================
// Shared.
// =================================

void init_shared_meta(seqan3::argument_parser & parser);
void try_parsing(seqan3::argument_parser & parser);

template <typename arguments_t>
void init_shared_options(seqan3::argument_parser & parser, arguments_t & arguments)
{
    static_assert(std::same_as<arguments_t, build_arguments> || std::same_as<arguments_t, search_arguments>);
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

} // namespace hashmap
