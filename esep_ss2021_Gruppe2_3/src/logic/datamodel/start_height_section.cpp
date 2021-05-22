/*
 * start_height_section.cpp
 *
 *  Created on: 21.05.2021
 *      Author: Justin Hoffmann
 */

#include <logic/datamodel/start_height_section.h>

namespace logic {
namespace datamodel {

void StartHeightSection::enter_workpiece(Workpiece&) {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

} /* namespace datamodel */
} /* namespace logic */
