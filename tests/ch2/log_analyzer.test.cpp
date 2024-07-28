/* Copyright 2023 Abby */
#include "ch2/log_analyzer.hpp"

#include "doctest/doctest.h"
#include "fmt/core.h"

#include <iostream>
#include <vector>

struct log_analyzer_fixture {
    ch2::log_analyzer log_analyzer;
};

// 1. normal test case
TEST_CASE_FIXTURE(log_analyzer_fixture, "is_valid_log_file_name") {
    // bad extension return false
    CHECK_FALSE(
        log_analyzer.is_valid_log_file_name("file_with_bad_extension.foo"));

    // good lowercase extension return true
    // There is an error in the current implementation. To resolve this, you
    // need to refactor the function to ensure that the file extension is
    // converted to lowercase before performing the comparison.
    CHECK(log_analyzer.is_valid_log_file_name("file_with_good_extension.slf"));

    // good uppercase extension return true
    CHECK(log_analyzer.is_valid_log_file_name("file_with_good_extension.SLF"));

    // empty file name throw exception
    CHECK_THROWS_WITH(log_analyzer.is_valid_log_file_name(""),
                      doctest::Contains("file_name"));
}

// 2. parameterized test cases
TEST_CASE_FIXTURE(log_analyzer_fixture, "is_valid_log_file_name") {
    // used for parameterized tests
    struct test_data {
        std::string file_name;
        bool        expected = false;
    };

    std::vector<test_data> test_cases = {
        {"file_with_bad_extension.foo", false},
        {"file_with_good_extension.slf", true},
        {"file_with_good_extension.SLF", true}};

    for (const auto& test_case : test_cases) {
        CAPTURE(test_case.file_name);
        CHECK(log_analyzer.is_valid_log_file_name(test_case.file_name) ==
              test_case.expected);
    }
}

TEST_CASE_FIXTURE(
    log_analyzer_fixture,
    "is_valid_log_file_name when called changes was_last_file_name_valid_") {
    // used for parameterized tests
    struct test_data {
        std::string file_name;
        bool        expected = false;
    };

    std::vector<test_data> test_cases = {{"bad_file.foo", false},
                                         {"good_file.slf", true}};

    for (const auto& test_case : test_cases) {
        CAPTURE(test_case.file_name);
        log_analyzer.is_valid_log_file_name(test_case.file_name);
        CHECK(log_analyzer.was_last_file_name_valid() == test_case.expected);
    }
}
