/*
 * start_height_section.h
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#ifndef SRC_LOGIC_DATAMODEL_START_HEIGHT_SECTION_H_
#define SRC_LOGIC_DATAMODEL_START_HEIGHT_SECTION_H_

#include "cb_section.h"

namespace logic {
namespace datamodel {

class StartHeightSection: public CBSection {
public:
    void enter_workpiece(Workpiece&);
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_START_HEIGHT_SECTION_H_ */
