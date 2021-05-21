/*
 * cb_section.h
 *
 *  Created on: 21.05.2021
 *      Author: justi
 */

#ifndef SRC_LOGIC_DATAMODEL_CB_SECTION_H_
#define SRC_LOGIC_DATAMODEL_CB_SECTION_H_

#include <queue>
#include "workpiece.h"

namespace logic {
namespace datamodel {

class CBSection {
public:
    CBSection(CBSection&);
    virtual ~CBSection();

    int size();
    Workpiece& back();
    Workpiece& front();
    void transfer();
    void exit_first();

private:
    std::queue<Workpiece> _queue;
    CBSection& _next_section;
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_CB_SECTION_H_ */
