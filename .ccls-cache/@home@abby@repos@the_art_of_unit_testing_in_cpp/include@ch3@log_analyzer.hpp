/* Copyright 2023 Abby */
#ifndef CH3_LOG_ANALYZER_HPP
#define CH3_LOG_ANALYZER_HPP

#include "fmt/format.h"

#include <algorithm>
#include <exception>
#include <memory>
#include <string>

namespace ch3 {

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

// extact interface from class
struct extension_manager_interface {
    virtual bool is_valid(std::string file_name) = 0;
    virtual ~extension_manager_interface()       = default;
};

// extract class
struct file_extension_manager : extension_manager_interface {
    bool is_valid(std::string file_name) override;
};

inline bool file_extension_manager::is_valid(std::string file_name) {
    // read some file here
    std::string extension = ".slf";
    if (file_name.size() >= extension.size()) {
        std::transform(file_name.rbegin(),
                       file_name.rbegin() + extension.size(),
                       file_name.rbegin(),
                       [](unsigned char c) { return std::tolower(c); });

        if (file_name.compare(file_name.size() - extension.size(),
                              extension.size(),
                              extension) == 0) {
            return true;
        }
    }

    if (file_name.empty()) {
        throw empty_file_name_exception("file_name has to be provided");
    }
    return true;
}

class extension_manager_factory {
 public:
    static extension_manager_interface* make_extension_manager();
    static void custom_manager(extension_manager_interface* custom_manager);

 private:
    inline static std::unique_ptr<extension_manager_interface> custom_manager_;
};

inline extension_manager_interface*
extension_manager_factory::make_extension_manager() {
    if (custom_manager_ != nullptr) { return custom_manager_.get(); }
    custom_manager_.reset(new file_extension_manager {});
    return custom_manager_.get();
}

inline void extension_manager_factory::custom_manager(
    extension_manager_interface* custom_manager) {
    custom_manager_.reset(custom_manager);
}

class log_analyzer {
 public:
    bool is_valid_log_file_name_1(const std::string& file_name);
    bool is_valid_log_file_name_2(const std::string& file_name);
    log_analyzer();
    log_analyzer(
        struct extension_manager_interface* extension_manager_interface);

    void extension_manager_interface(
        struct extension_manager_interface* extension_manager_interface);

 private:
    struct extension_manager_interface* extension_manager_interface_;
};

inline log_analyzer::log_analyzer() {
    extension_manager_interface_ =
        extension_manager_factory::make_extension_manager();
}

inline log_analyzer::log_analyzer(
    struct extension_manager_interface* extension_manager_interface)
    : extension_manager_interface_(extension_manager_interface) {}

inline void log_analyzer::extension_manager_interface(
    struct extension_manager_interface* extension_manager_interface) {
    extension_manager_interface_ = extension_manager_interface;
}

inline bool
log_analyzer::is_valid_log_file_name_1(const std::string& file_name) {
    struct file_extension_manager file_extension_manager;
    return file_extension_manager.is_valid(file_name);
}

inline bool
log_analyzer::is_valid_log_file_name_2(const std::string& file_name) {
    return extension_manager_interface_->is_valid(file_name);
}

} // namespace ch3

#endif
