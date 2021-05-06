#include "sorting_mechanism.h"

namespace hal {

SortingMechanism::SortingMechanism(std::shared_ptr<GPIOWrapper> gpio) {
    _gpio = gpio;
}

}

