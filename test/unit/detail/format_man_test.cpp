// --------------------------------------------------------------------------------------------------------
// Copyright (c) 2006-2023, Knut Reinert & Freie Universität Berlin
// Copyright (c) 2016-2023, Knut Reinert & MPI für molekulare Genetik
// This file may be used, modified and/or redistributed under the terms of the 3-clause BSD-License
// shipped with this file and also available at: https://github.com/seqan/sharg-parser/blob/main/LICENSE.md
// --------------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <sharg/parser.hpp>

// Reused global variables
struct format_man_test : public ::testing::Test
{
    int option_value{5};
    bool flag_value{false};
    int8_t non_list_pos_opt_value{1};
    std::vector<std::string> list_pos_opt_value{};
    std::string my_stdout{};
    static constexpr std::array argv{"./format_man_test", "--version-check", "false", "--export-help", "man"};
    std::string const version_str{sharg::sharg_version_cstring};
    std::string expected = R"(.TH DEFAULT 1 "December 01, 1994" "default 01.01.01" "default_man_page_title")"
                           "\n"
                           R"(.SH NAME)"
                           "\n"
                           R"(default \- A short description here.)"
                           "\n"
                           R"(.SH SYNOPSIS)"
                           "\n"
                           R"(\fB./format_man_test\fP synopsis)"
                           "\n"
                           R"(.br)"
                           "\n"
                           R"(\fB./format_man_test\fP synopsis2)"
                           "\n"
                           R"(.SH DESCRIPTION)"
                           "\n"
                           R"(description)"
                           "\n"
                           R"(.sp)"
                           "\n"
                           R"(description2)"
                           "\n"
                           R"(.SH POSITIONAL ARGUMENTS)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fBARGUMENT-1\fP (\fIsigned 8 bit integer\fP))"
                           "\n"
                           R"(this is a positional option.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fBARGUMENT-2\fP (\fIList\fP of \fIstd::string\fP))"
                           "\n"
                           R"(this is a positional option. Default: [])"
                           "\n"
                           R"(.SH OPTIONS)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-i\fP, \fB--int\fP (\fIsigned 32 bit integer\fP))"
                           "\n"
                           R"(this is a int option. Default: A number)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-j\fP, \fB--jint\fP (\fIsigned 32 bit integer\fP))"
                           "\n"
                           R"(this is a required int option.)"
                           "\n"
                           R"(.SH FLAGS)"
                           "\n"
                           R"(.SS SubFlags)"
                           "\n"
                           R"(here come all the flags)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-f\fP, \fB--flag\fP)"
                           "\n"
                           R"(this is a flag.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-k\fP, \fB--kflag\fP)"
                           "\n"
                           R"(this is a flag.)"
                           "\n"
                           R"(.SS Common options)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-h\fP, \fB--help\fP)"
                           "\n"
                           R"(Prints the help page.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-hh\fP, \fB--advanced-help\fP)"
                           "\n"
                           R"(Prints the help page including advanced options.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--version\fP)"
                           "\n"
                           R"(Prints the version information.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--copyright\fP)"
                           "\n"
                           R"(Prints the copyright/license information.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--export-help\fP (std::string))"
                           "\n"
                           R"(Export the help page information. Value must be one of )"
#if SHARG_HAS_TDL
                           "[html, man, ctd, cwl]."
#else
                           "[html, man]."
#endif
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--version-check\fP (bool))"
                           "\n"
                           R"(Whether to check for the newest app version. Default: true)"
                           "\n"
                           R"(.SH EXAMPLES)"
                           "\n"
                           R"(example)"
                           "\n"
                           R"(.sp)"
                           "\n"
                           R"(example2)"
                           "\n"
                           R"(.SH VERSION)"
                           "\n"
                           R"(\fBLast update: \fRDecember 01, 1994)"
                           "\n"
                           R"(.br)"
                           "\n"
                           R"(\fBdefault version: \fR01.01.01)"
                           "\n"
                           R"(.br)"
                           "\n"
                           R"(\fBSharg version: \fR)"
                         + version_str + "\n";

    // Full info parser initialisation
    void dummy_init(sharg::parser & parser)
    {
        parser.info.date = "December 01, 1994";
        parser.info.version = "01.01.01";
        parser.info.man_page_title = "default_man_page_title";
        parser.info.short_description = "A short description here.";
        parser.info.synopsis.push_back("./format_man_test synopsis");
        parser.info.synopsis.push_back("./format_man_test synopsis2");
        parser.info.description.push_back("description");
        parser.info.description.push_back("description2");
        parser.add_option(option_value,
                          sharg::config{.short_id = 'i',
                                        .long_id = "int",
                                        .description = "this is a int option.",
                                        .default_message = "A number"});
        parser.add_option(option_value,
                          sharg::config{.short_id = 'j',
                                        .long_id = "jint",
                                        .description = "this is a required int option.",
                                        .required = true});
        parser.add_section("Flags");
        parser.add_subsection("SubFlags");
        parser.add_line("here come all the flags");
        parser.add_flag(flag_value,
                        sharg::config{.short_id = 'f', .long_id = "flag", .description = "this is a flag."});
        parser.add_flag(flag_value,
                        sharg::config{.short_id = 'k', .long_id = "kflag", .description = "this is a flag."});
        parser.add_positional_option(non_list_pos_opt_value,
                                     sharg::config{.description = "this is a positional option."});
        parser.add_positional_option(list_pos_opt_value, sharg::config{.description = "this is a positional option."});
        parser.info.examples.push_back("example");
        parser.info.examples.push_back("example2");
    }
};

TEST_F(format_man_test, empty_information)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};
    parser.info.date = "December 01, 1994";
    parser.info.version = "01.01.01";
    parser.info.man_page_title = "default_man_page_title";
    parser.info.short_description = "A short description here.";

    std::string const version_str{sharg::sharg_version_cstring};
    std::string expected_short = R"(.TH DEFAULT 1 "December 01, 1994" "default 01.01.01" "default_man_page_title")"
                                 "\n"
                                 R"(.SH NAME)"
                                 "\n"
                                 R"(default \- A short description here.)"
                                 "\n"
                                 R"(.SH OPTIONS)"
                                 "\n"
                                 R"(.SS Common options)"
                                 "\n"
                                 R"(.TP)"
                                 "\n"
                                 R"(\fB-h\fP, \fB--help\fP)"
                                 "\n"
                                 R"(Prints the help page.)"
                                 "\n"
                                 R"(.TP)"
                                 "\n"
                                 R"(\fB-hh\fP, \fB--advanced-help\fP)"
                                 "\n"
                                 R"(Prints the help page including advanced options.)"
                                 "\n"
                                 R"(.TP)"
                                 "\n"
                                 R"(\fB--version\fP)"
                                 "\n"
                                 R"(Prints the version information.)"
                                 "\n"
                                 R"(.TP)"
                                 "\n"
                                 R"(\fB--copyright\fP)"
                                 "\n"
                                 R"(Prints the copyright/license information.)"
                                 "\n"
                                 R"(.TP)"
                                 "\n"
                                 R"(\fB--export-help\fP (std::string))"
                                 "\n"
                                 R"(Export the help page information. Value must be one of )"
#if SHARG_HAS_TDL
                                 "[html, man, ctd, cwl]."
#else
                                 "[html, man]."
#endif
                                 "\n"
                                 R"(.TP)"
                                 "\n"
                                 R"(\fB--version-check\fP (bool))"
                                 "\n"
                                 R"(Whether to check for the newest app version. Default: true)"
                                 "\n"
                                 R"(.SH VERSION)"
                                 "\n"
                                 R"(\fBLast update: \fRDecember 01, 1994)"
                                 "\n"
                                 R"(.br)"
                                 "\n"
                                 R"(\fBdefault version: \fR01.01.01)"
                                 "\n"
                                 R"(.br)"
                                 "\n"
                                 R"(\fBSharg version: \fR)"
                               + version_str + "\n";

    // Test the dummy parser with minimal information.
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected_short);
}

TEST_F(format_man_test, full_information)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);
    // Test the dummy parser without any copyright or citations.
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected);
}

TEST_F(format_man_test, full_info_short_copyright)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);
    // Add a short copyright and test the dummy parser.
    parser.info.short_copyright = "short copyright";
    expected += R"(.SH LEGAL
\fBdefault Copyright: \fRshort copyright
.br
\fBSeqAn Copyright: \fR2006-2023 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
)";
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected);
}

TEST_F(format_man_test, full_info_short_and_citation)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);
    // Add a short copyright & citation and test the dummy parser.
    parser.info.short_copyright = "short copyright";
    parser.info.citation = "citation";
    expected += R"(.SH LEGAL
\fBdefault Copyright: \fRshort copyright
.br
\fBSeqAn Copyright: \fR2006-2023 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
.br
\fBIn your academic works please cite: \fRcitation
)";
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected);
}

TEST_F(format_man_test, full_info_short_long_and_citation)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);
    // Add a short copyright & citation & long copyright and test the dummy parser.
    parser.info.short_copyright = "short copyright";
    parser.info.citation = "citation";
    parser.info.long_copyright = "looong copyright";
    expected += R"(.SH LEGAL
\fBdefault Copyright: \fRshort copyright
.br
\fBSeqAn Copyright: \fR2006-2023 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
.br
\fBIn your academic works please cite: \fRcitation
.br
For full copyright and/or warranty information see \fB--copyright\fR.
)";
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected);
}

TEST_F(format_man_test, full_info_author)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);
    // Add a short copyright and test the dummy parser.
    parser.info.author = "author";
    expected += R"(.SH LEGAL
\fBAuthor: \fRauthor
.br
\fBSeqAn Copyright: \fR2006-2023 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
)";
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected);
}

TEST_F(format_man_test, full_info_email)
{
    // Create the dummy parser.
    sharg::parser parser{"default", argv.size(), argv.data()};

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);
    // Add a short copyright and test the dummy parser.
    parser.info.email = "email";
    expected += R"(.SH LEGAL
\fBContact: \fRemail
.br
\fBSeqAn Copyright: \fR2006-2023 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
)";
    testing::internal::CaptureStdout();
    EXPECT_EXIT(parser.parse(), ::testing::ExitedWithCode(EXIT_SUCCESS), "");

    my_stdout = testing::internal::GetCapturedStdout();
    EXPECT_EQ(my_stdout, expected);
}
