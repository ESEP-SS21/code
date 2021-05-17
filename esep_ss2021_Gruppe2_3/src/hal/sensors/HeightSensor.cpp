/*
 * HeightSensor.cpp
 *
 *  Created on: 13.05.2021
 *      Author: Lasse
 */

#include <hal/sensors/HeightSensor.h>

HeightSensor::HeightSensor() {
    _adc_bank = mmap_device_io(ADC_ADDRESS_LENGTH, ADC_START_ADDRESS);
    out32(ADC_IRQ_ENABLE_SET(_adc_bank), 0x2);
}

void HeightSensor::sample(){
    out32(ADC_CTRL(_adc_bank), 0x1);
}

void HeightSensor::reset_interrupt(){
    out32(ADC_IRQ_STATUS(_adc_bank), 0x2);
}

float HeightSensor::convert_to_mm(int height){
    return 1;
}

void HeightSensor::set_zero_point(int zero_point){
    _zero_point = zero_point;
}

int HeightSensor::get_value(){
    uint32_t data = in32(ADC_DATA(_adc_bank));
    return data;
}

HeightSensor::~HeightSensor() {

}
