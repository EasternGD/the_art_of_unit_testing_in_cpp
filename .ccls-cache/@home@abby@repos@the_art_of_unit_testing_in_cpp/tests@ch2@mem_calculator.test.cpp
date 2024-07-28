/* Copyright 2023 Abby */
#include "ch2/mem_calculator.hpp"

#include "doctest/doctest.h"
#include "fmt/core.h"

struct mem_calculater_fixture {
 public:
    using value_type = sample::mem_calculator;
    using pointer    = std::unique_ptr<sample::mem_calculator>;
    using reference  = value_type&;

    reference make_mem_calculater() {
        mem_calculater_ = std::make_unique<sample::mem_calculator>();
        return *mem_calculater_;
    }

 private:
    pointer mem_calculater_;
};

TEST_CASE_FIXTURE(mem_calculater_fixture, "sum() by default return zero") {
    auto& mem_calculator = make_mem_calculater();
    auto  sum            = mem_calculator.sum();
    REQUIRE_EQ(0, sum);
}

TEST_CASE_FIXTURE(mem_calculater_fixture,
                  "add() when called change mem_calculator.sum_") {
    auto& mem_calculator = make_mem_calculater();
    mem_calculator.add(1);
    auto sum = mem_calculator.sum();
    REQUIRE_EQ(1, sum);
}

