#pragma once


#include <nlohmann/json.hpp> 

using nlohmann::json;
namespace dispatcher{

inline void to_json(json& j, const Event& e) {
    j = json { { "type", e.type }, { "payl", e.payload }, { "broad", e.broadcast } };
}

inline void from_json(const json& j, Event& e) {
    j.at("type").get_to(e.type);
    j.at("payl").get_to(e.payload);
    j.at("broad").get_to(e.broadcast);
}

}
