/* Copyright 2023 Abby */
#ifndef CH2_LOG_ANALYZER_HPP
#define CH2_LOG_ANALYZER_HPP

#include "fmt/format.h"

#include <algorithm>
#include <exception>
#include <string>

namespace ch2 {

class empty_file_name_exception : public std::exception {
 public:
    explicit empty_file_name_exception(const std::string& message)
        : message_ {message} {}

    const char* what() const noexcept override;

 private:
    std::string message_;
};

inline const char* empty_file_name_exception::what() const noexcept {
    return message_.data();
}

class log_analyzer {
 public:
    bool        is_valid_log_file_name(std::string file_name);
    const bool& was_last_file_name_valid();

 private:
    bool was_last_file_name_valid_ = false;
};

inline bool log_analyzer::is_valid_log_file_name(std::string file_name) {
    was_last_file_name_valid_ = false;
    std::string extension     = ".slf";
    if (file_name.size() >= extension.size()) {
        std::transform(file_name.rbegin(),
                       file_name.rbegin() + extension.size(),
                       file_name.rbegin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (file_name.compare(file_name.size() - extension.size(),
                              extension.size(),
                              extension) == 0) {
            was_last_file_name_valid_ = true;
            return true;
        }
    }

    if (file_name.empty()) {
        throw empty_file_name_exception("file_name has to be provided");
    }
    return false;
}

inline const bool& log_analyzer::was_last_file_name_valid() {
    return was_last_file_name_valid_;
}

} // namespace ch2

#endif
