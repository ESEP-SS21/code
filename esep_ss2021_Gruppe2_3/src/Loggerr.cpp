
#include <Logger.h>

namespace Logger {

void Internal::setup(const std::string &name, bool console, const std::string &file){
    _name = name;
    std::vector<spdlog::sink_ptr> sinks;

    if (file != "") {
        auto file_logger = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file);
        sinks.push_back(file_logger);
    }

    if (console) {
        auto console_logger = std::make_shared<spdlog::sinks::stdout_sink_mt>();
        sinks.push_back(console_logger);
    }

    auto logger = std::make_shared<spdlog::logger>(_name, begin(sinks), end(sinks));

    spdlog::register_logger(logger);
}

} /* namespace Logger */
