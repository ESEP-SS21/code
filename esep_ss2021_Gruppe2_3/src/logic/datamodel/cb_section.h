/*
 * cb_section.h
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#ifndef SRC_LOGIC_DATAMODEL_CB_SECTION_H_
#define SRC_LOGIC_DATAMODEL_CB_SECTION_H_

#include <queue>
#include <mutex>
#include "workpiece.h"


namespace logic {
namespace datamodel {

class CBSection {
public:
    CBSection(std::shared_ptr<CBSection> next_section);

    int size();
    const Workpiece& back();
    const Workpiece& front();
    void transfer();
    void enter_workpiece(Workpiece&);
    void exit_first();

protected:
    mutable std::mutex _section_mutex;
    std::unique_ptr<std::queue<Workpiece>> _queue;
    std::shared_ptr<CBSection> _next_section;
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_CB_SECTION_H_ */
