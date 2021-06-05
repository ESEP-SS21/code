#pragma once

#include "logic/datamodel/workpiece.h"

namespace test {
namespace logic {
using namespace ::logic::datamodel;

inline Workpiece create_wp_hm(){
    Workpiece wp_hm;
    wp_hm.height_1 = Workpiece::height_bohrung;
    wp_hm.is_metallic = true;
    wp_hm.determine_type();
    return wp_hm;
}

inline Workpiece create_wp_hb(){
    Workpiece wp_hb;
    wp_hb.height_1 = Workpiece::height_bohrung;
    wp_hb.determine_type();
    return wp_hb;
}

inline Workpiece create_wp_h(){
    Workpiece wp_h;
    wp_h.height_1 = Workpiece::height_high;
    wp_h.determine_type();
    return wp_h;
}

inline Workpiece create_wp_l(){
    Workpiece wp_l;
    wp_l.height_1 = Workpiece::height_low;
    wp_l.determine_type();
    return wp_l;
}

inline Workpiece create_wp_unknown(){
    Workpiece wp_l;
    wp_l.height_1 = 1;
    wp_l.determine_type();
    return wp_l;
}


} /*namespace*/
} /*namespace*/
