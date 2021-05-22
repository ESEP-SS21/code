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

}

const Workpiece& CBSection::back() {

}

const Workpiece& CBSection::front() {

}

void CBSection::transfer() {

}

void CBSection::exit_first() {

}

} /* namespace datamodel */
} /* namespace logic */
