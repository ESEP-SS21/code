
#include "Logger.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "utils.h"


namespace Logger {

void Internal::setup(const std::string &name, spdlog::level::level_enum console, spdlog::level::level_enum file){
    _name = name;
    std::vector<spdlog::sink_ptr> sinks;

    if (file) {
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/" + utils::current_time_and_date + ".txt");
        file_sink->set_level(file);
        sinks.push_back(file_sink);
    }

    if (console) {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
        console_sink ->set_level(console);
        sinks.push_back(console_sink);
    }

    auto logger = std::make_shared<spdlog::logger>(_name, begin(sinks), end(sinks));

    spdlog::register_logger(logger);
}

} /* namespace Logger */
