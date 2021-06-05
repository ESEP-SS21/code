#include <logic/datamodel/cb_section.h>

#include <utility>

namespace logic {
namespace datamodel {

CBSection::CBSection() :
    _queue(std::make_shared<std::queue<Workpiece>>()),
    _next_section(nullptr) {
}

CBSection::CBSection(std::shared_ptr<CBSection> next_section) :
    _next_section(std::move(next_section)),
    _queue(std::make_shared<std::queue<Workpiece>>()) {
}

int CBSection::workpiece_count() const {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    return static_cast<int>(this->_queue->size());
}

const Workpiece &CBSection::last_workpiece() const {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    return this->_queue->back();
}

const Workpiece &CBSection::first_workpiece() const {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    return this->_queue->front();
}

void CBSection::enter_workpiece(const Workpiece &wrpc) const {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    this->_queue->push(wrpc);
}

void CBSection::exit_first_workpiece() const {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    if (!_queue->empty()) {
        this->_queue->pop();
    }
}

void CBSection::transfer_first_workpiece() const {
    const std::lock_guard<std::mutex> lock(_section_mutex);
    if ((this->_next_section != nullptr) && (!this->_queue->empty())) {
        this->_next_section->enter_workpiece(this->_queue->front());
    }
    if (!this->_queue->empty()) {
        this->_queue->pop();
    }
}

std::shared_ptr<CBSection> CBSection::get_next_section() const {
    return _next_section;
}

} /* namespace datamodel */
} /* namespace logic */
