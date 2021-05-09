#pragma once
#include <string>
#include <iomanip> // put_time
#include <ctime>   // localtime
#include <sstream>

namespace utils {

inline std::string calc_current_time_and_date();

const std::chrono::system_clock::time_point start_time { std::chrono::system_clock::now() };
const std::string current_time_and_date = calc_current_time_and_date();

inline std::string calc_current_time_and_date() {
    auto in_time_t = std::chrono::system_clock::to_time_t(start_time);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%H-%M");
    return ss.str();
}
}
