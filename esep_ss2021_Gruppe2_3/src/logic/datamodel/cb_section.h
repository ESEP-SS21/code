#pragma once

#include <queue>
#include <mutex>
#include "workpiece.h"

namespace logic {
namespace datamodel {

class CBSection {
public:
    CBSection();
    CBSection(std::shared_ptr<CBSection> next_section);
    virtual ~CBSection() = default;

    int workpiece_count() const;
    const Workpiece& first_workpiece() const;
    const Workpiece& last_workpiece() const;
    void enter_workpiece(const Workpiece&) const;
    void transfer_first_workpiece() const;
    void exit_first_workpiece() const;

    std::shared_ptr<std::queue<Workpiece>> get_queue();
    std::shared_ptr<CBSection> get_next_section();

protected:
    mutable std::mutex _section_mutex;
    std::shared_ptr<std::queue<Workpiece>> _queue;
    std::shared_ptr<CBSection> _next_section;
};

} /* namespace datamodel */
} /* namespace logic */