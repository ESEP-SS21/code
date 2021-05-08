#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Logger {

using Logger = std::shared_ptr<spdlog::logger>;

static std::string _name = "";

inline std::shared_ptr<spdlog::logger> get(){
    return spdlog::get(_name);
}

inline void setup(const std::string &name, bool console, const std::string &file = "") {
    _name = name;

    std::vector<spdlog::sink_ptr> sinks;

    if (file != ""){
        auto file_logger = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file);
        sinks.push_back(file_logger);
    }

    if (console){
        auto console_logger = std::make_shared<spdlog::sinks::stdout_sink_mt>();
        sinks.push_back(console_logger);
    }

    auto logger = std::make_shared<spdlog::logger>(_name, begin(sinks), end(sinks));

    spdlog::register_logger(logger);
}

} /* namespace */
