#ifndef SRC_ACTUATORS_SORTING_MECHANISM_H_
#define SRC_ACTUATORS_SORTING_MECHANISM_H_

#include "../gpiowrapper.h"

namespace hal {

class SortingMechanism {
protected:
    std::shared_ptr<GPIOWrapper> _gpio;

public:
    SortingMechanism(std::shared_ptr<GPIOWrapper> gpio);
    virtual ~SortingMechanism() = default;
    virtual void discard() const = 0;
    virtual void do_not_discard() const = 0;
    virtual bool is_open() const = 0;
    virtual void reset() const = 0;
};

}

#endif /* SRC_ACTUATORS_SORTING_MECHANISM_H_ */
