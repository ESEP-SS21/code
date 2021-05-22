/*
 * cb_section.cpp
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#include <logic/datamodel/cb_section.h>

namespace logic {
namespace datamodel {

CBSection::CBSection(const CBSection& next_section) : _next_section(next_section) {

}

CBSection::~CBSection() {

}

int CBSection::size() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

const Workpiece& CBSection::back() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

const Workpiece& CBSection::front() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

void CBSection::transfer() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

void CBSection::exit_first() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

} /* namespace datamodel */
} /* namespace logic */
