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
    CBSection();
    CBSection(std::shared_ptr<CBSection> next_section);

    /**
     * Anzahl der Workpieces in der CBSection
     */
    int size() const;

    /**
     * Workpiece an der hintersten Stelle (links) der CBSection
     */
    const Workpiece& back() const;

    /**
     * Workpiece an der vordersten Stelle (rechts) der CBSection
     */
    const Workpiece& front() const;

    /**
     * Transferiert das vorderste Workpiece in die naechste CBSection
     */
    void transfer() const ;

    /**
     * Packt ein Workpiece hinten in die CBSectoin
     */
    void enter_workpiece(const Workpiece&) const;

    /**
     * Entfernt das vorderste Workpiece aus der CBSection
     */
    void exit_first() const;

protected:
    mutable std::mutex _section_mutex;
    std::unique_ptr<std::queue<Workpiece>> _queue;
    std::shared_ptr<CBSection> _next_section;
};

} /* namespace datamodel */
} /* namespace logic */

#endif /* SRC_LOGIC_DATAMODEL_CB_SECTION_H_ */
