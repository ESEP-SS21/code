#pragma once

#include <cstdint>
#include "workpiece_type.h"
#include "encoded_workpiece.h"

namespace logic {
namespace datamodel {

using id = uint32_t;

class Workpiece {
public:
    Workpiece();
    Workpiece(EncodedWorkpiece&);
    virtual ~Workpiece() = default;

    std::shared_ptr<EncodedWorkpiece> encode() const;
    void determine_workpiece_type();

    id wrpc_id;
    WorkpieceType type = WorkpieceType::Unknown;
    /*
     * In 0.1mm
     */
    int height_1 = 0;
    /*
     * In 0.1mm
     */
    int height_2 = 0;
    bool is_metallic = false;
    bool is_flipped = false;


private:
    /**
     * used for automatic id assignment in ctor
     */
    static id _last_id;
    static constexpr int max_id = 1 << 21;

    static constexpr int height_high = 252;
    static constexpr int height_low = 210;
    static constexpr int height_bohrung = 91;
    static constexpr int height_tolerance = 20;

    bool height_is_within_tolerance(int expected, int actual){
        return (actual >= expected - height_tolerance) && (actual <= expected + height_tolerance);
    }
};

} /* namespace datamodel */
} /* namespace logic*/
