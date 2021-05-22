/*
 * workpiece.h
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_LOGIC_DATAMODEL_WORKPIECE_H_
#define SRC_LOGIC_DATAMODEL_WORKPIECE_H_

#include <cstdint>
#include "workpiece_type.h"
#include "encoded_workpiece.h"

namespace logic {
namespace datamodel {

#define HEIGHT_TOLERANCE 20 //adjustable

#define HIGH_INTERVALL_MIN 250-HEIGHT_TOLERANCE
#define HIGH_INTERVALL_MAX 254+HEIGHT_TOLERANCE

#define LOW_INTERVALL_MIN 210-HEIGHT_TOLERANCE
#define LOW_INTERVALL_MAX 210+HEIGHT_TOLERANCE

#define BOHRUNG_INTERVALL_MIN 86-HEIGHT_TOLERANCE
#define BOHRUNG_INTERVALL_MAX 96+HEIGHT_TOLERANCE

#define IS_HIGH(x) (x >= HIGH_INTERVALL_MIN) && (x <= HIGH_INTERVALL_MAX)
#define IS_LOW(x) (x >= LOW_INTERVALL_MIN) && (x <= LOW_INTERVALL_MAX)
#define HAS_BOHRUNG(x) (x >= BOHRUNG_INTERVALL_MIN) && (x <= BOHRUNG_INTERVALL_MAX)

using id = uint32_t;

class Workpiece {
public:
    id wrpc_id;
    WorkpieceType type = WorkpieceType::unknown;
    int height_1 = 0;
    int height_2 = 0;
    bool is_metallic = false;
    bool is_flipped = false;

    Workpiece();
    Workpiece(EncodedWorkpiece&);

    std::shared_ptr<EncodedWorkpiece> encode() const;
    void determine_workpiece_type();

private:
    /**
     * automatische ID-Zuweisung
     */
    static id _last_id;
};

} /* namespace datamodel */
} /* namespace logic*/

#endif /* SRC_LOGIC_DATAMODEL_WORKPIECE_H_ */
