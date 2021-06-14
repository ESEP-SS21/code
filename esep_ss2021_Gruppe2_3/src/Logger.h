#pragma once

#include "spdlog/spdlog.h"

namespace Logger {

using Logger = std::shared_ptr<spdlog::logger>;
using StmLogger = spdlog::logger*;

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
    void setup(const std::string &name, bool console, bool file);

};

inline std::shared_ptr<spdlog::logger> get() {
    auto& t = Internal::get_instance();
    return t.get();
}

inline spdlog::logger* getStmLogger() {
    return get().get();
}


inline void setup(const std::string &name, bool console, bool file) {
    Internal::get_instance().setup(name, console, file);
}

} /* namespace */
