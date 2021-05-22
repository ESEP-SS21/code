/*
 * cb_section.cpp
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#include <logic/datamodel/cb_section.h>

namespace logic {
namespace datamodel {

CBSection::CBSection(std::shared_ptr<CBSection> next_section) : _next_section(next_section) {}

int CBSection::size() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    return static_cast<int>(this->_queue->size());
}

const Workpiece& CBSection::back() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    return this->_queue->back();
}

const Workpiece& CBSection::front() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    return this->_queue->front();
}

void CBSection::enter_workpiece(Workpiece& wrpc) {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    this->_queue->push(wrpc);
}

void CBSection::exit_first() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    this->_queue->pop();
}

void CBSection::transfer() {
    const std::lock_guard<std::mutex> lock(_section_mutex);
}

} /* namespace datamodel */
} /* namespace logic */
