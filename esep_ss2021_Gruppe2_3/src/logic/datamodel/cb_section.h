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
    std::shared_ptr<Workpiece> first_workpiece() const;
    std::shared_ptr<Workpiece> last_workpiece() const;
    void enter_workpiece(const Workpiece&) const;
    void transfer_first_workpiece() const;
    void exit_first_workpiece() const;
    std::shared_ptr<CBSection> get_next_section() const;

protected:
    mutable std::mutex _section_mutex;
    const std::unique_ptr<std::queue<Workpiece>> _queue;
    const std::shared_ptr<CBSection> _next_section;
private:
    bool log_if_empty() const;
};

} /* namespace datamodel */
} /* namespace logic */
