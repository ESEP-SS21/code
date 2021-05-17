/*
 * HeightSensor.cpp
 *
 *  Created on: 13.05.2021
 *      Author: Lasse
 */

#include <hal/sensors/HeightSensor.h>

HeightSensor::HeightSensor(int chid) {
    // TODO Auto-generated constructor stub

}

void HeightSensor::sample(){

}

float HeightSensor::convert_to_mm(int height){
    return 1;
}

void HeightSensor::set_zero_point(){

}

char HeightSensor::get_event_number(){
    return _event_number;
}

HeightSensor::~HeightSensor() {
    // TODO Auto-generated destructor stub
}
