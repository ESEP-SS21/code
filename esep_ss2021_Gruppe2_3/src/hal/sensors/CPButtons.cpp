/*
 * CPButtons.cpp
 *
 *  Created on: 13.05.2021
 *      Author: morit
 */

#include <hal/sensors/CPButtons.h>

namespace hal {

CPButtons::CPButtons(std::shared_ptr<GPIOWrapper> gpio){
    _gpio=gpio;
}

bool CPButtons::was_pressed(CPButtonType){
    return true;
}

bool CPButtons::was_released(CPButtonType){
    return true;
}

CPButtons::~CPButtons(){

}
}



