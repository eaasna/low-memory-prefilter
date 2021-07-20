#pragma once

#include <shared.hpp>

#include <seqan3/argument_parser/all.hpp>

namespace hashmap
{

// =================================
// Validators.
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
