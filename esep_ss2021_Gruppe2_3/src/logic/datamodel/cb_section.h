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
    CBSection(const CBSection& next_section);
    virtual ~CBSection();

    int size();
    const Workpiece& back();
    const Workpiece& front();
    void transfer();
    void exit_first();

protected:
    mutable std::mutex _section_mutex;
    std::unique_ptr<std::queue<Workpiece>> _queue;
    const CBSection& _next_section;
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_CB_SECTION_H_ */
