/* Copyright 2023 Abby */
#include "ch3/log_analyzer.hpp"

#include "doctest/doctest.h"
#include "fmt/core.h"

#include <exception>

class alway_valid_fake_extension_manager : ch3::extension_manager_interface {
    bool is_valid(std::string file_name) override { return true; }
};

class fake_exception : public std::exception {
 public:
    explicit fake_exception(const std::string& message)
        : message_ {message} {}

    const char* what() const noexcept override { return message_.data(); };

 private:
    std::string message_;
};

struct fake_extension_manager : ch3::extension_manager_interface {
    bool will_be_valid_ = false;
    bool will_throw_    = false;
    bool is_valid(std::string file_name) override {
        if (will_throw_) { throw fake_exception("this is fake"); }
        return will_be_valid_;
    }
};

struct log_analyzer_fixture {
 public:
    using value_type = ch3::log_analyzer;
    using pointer    = std::unique_ptr<ch3::log_analyzer>;
    using reference  = value_type&;

    reference make_log_analyzer() {
        struct fake_extension_manager fake_extension_manager;
        log_analyzer_ =
            std::make_unique<ch3::log_analyzer>(&fake_extension_manager);
        return *log_analyzer_;
    }

 private:
    pointer log_analyzer_;
};

// use constructor to inject dependency
TEST_CASE("is_valid_log_file_name()/name supported extension/return true") {
    auto fake_extension_manager           = ::fake_extension_manager {};
    fake_extension_manager.will_be_valid_ = true;
    auto log    = ch3::log_analyzer {&fake_extension_manager};
    bool result = log.is_valid_log_file_name_2("short.ext");
    REQUIRE(result);
}

// use fake exception to test exception
TEST_CASE(
    "is_valid_log_file_name()/extend_manager throws exception/return true") {
    auto fake_extension_manager           = ::fake_extension_manager {};
    fake_extension_manager.will_be_valid_ = true;
    fake_extension_manager.will_throw_    = true;
    auto log = ch3::log_analyzer {&fake_extension_manager};
    // we don't need return true in doctest, because we can check thows with
    // doctest.
    CHECK_THROWS_WITH(log.is_valid_log_file_name_2("short.ext"),
                      doctest::Contains("fake"));
}

// use get/set to inject dependency
TEST_CASE("is_valid_log_file_name()/name supported extension/return true") {
    auto fake_extension_manager           = ::fake_extension_manager {};
    fake_extension_manager.will_be_valid_ = true;
    auto log                              = ch3::log_analyzer {};
    log.extension_manager_interface(&fake_extension_manager);
    bool result = log.is_valid_log_file_name_2("short.ext");
    REQUIRE(result);
}

// use factory to create extension manager
TEST_CASE("is_valid_log_file_name()/name supported extension/return true") {
    auto* fake_extension_manager           = new ::fake_extension_manager {};
    fake_extension_manager->will_be_valid_ = true;
    ch3::extension_manager_factory::custom_manager(fake_extension_manager);

    auto log    = ch3::log_analyzer {};
    bool result = log.is_valid_log_file_name_2("short.ext");
    REQUIRE(result);
}
