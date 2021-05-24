#pragma once
#include <string>
#include <iomanip> // put_time
#include <ctime>   // localtime
#include <sstream>

namespace utils {

auto const start_time = std::chrono::system_clock::now();

inline std::string current_time_and_date_string() {
    auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%H-%M");
    return ss.str();
}

const std::string system_start_time_and_date_string = current_time_and_date_string();

}
