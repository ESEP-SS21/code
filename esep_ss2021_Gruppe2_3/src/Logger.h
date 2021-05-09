#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/common.h"

namespace Logger {

using Logger = std::shared_ptr<spdlog::logger>;

class Internal {
private:
    Internal() = default;
    std::string _name {""};

public:
    virtual ~Internal() = default;

    static Internal& get_instance(){
        static Internal _instance;
        return _instance;
    }

    std::shared_ptr<spdlog::logger> get() const{
        return spdlog::get(_name);
    }
    void setup(const std::string &name, spdlog::level::level_enum console, spdlog::level::level_enum file);

};

inline std::shared_ptr<spdlog::logger> get() {
    auto& t = Internal::get_instance();
    return t.get();
}

inline void setup(const std::string &name, spdlog::level::level_enum console, spdlog::level::level_enum file) {
    Internal::get_instance().setup(name, console, file);
}

} /* namespace */
