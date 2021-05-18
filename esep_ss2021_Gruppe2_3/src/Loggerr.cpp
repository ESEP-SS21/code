#include "Logger.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"
#include <thread>

#include <string>

namespace Logger {

void Internal::setup(const std::string &name, bool console, const std::string &file) {
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

    spdlog::init_thread_pool(8192, 1);
    auto logger_async = std::make_shared<spdlog::async_logger>(_name, begin(sinks), end(sinks),
            spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    auto logger = std::make_shared<spdlog::logger>(_name, begin(sinks), end(sinks));

    spdlog::register_logger(logger);
}

void Internal::bench(int howmany) {

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    Logger l = get();

    std::string s = "Hello logger: ";

    auto start = high_resolution_clock::now();
    for (auto i = 0; i < howmany; ++i) {
        l->info(s + "msg number {}", i);
    }
    l->flush();

    auto delta = high_resolution_clock::now() - start;
    auto delta_d = duration_cast<duration<double>>(delta).count();
    l->info("Elapsed: {:0.2f} secs {:>16L}/sec", delta_d, int(howmany / delta_d));
}

} /* namespace Logger */
