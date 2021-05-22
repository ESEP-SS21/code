/*
 * HeightSensor.cpp
 *
 *  Created on: 13.05.2021
 *      Author: Lasse
 */

#include <hal/sensors/HeightSensor.h>

HeightSensor::HeightSensor(): _zero_point{0} {
    _adc_bank = mmap_device_io(ADC_ADDRESS_LENGTH, ADC_START_ADDRESS);
    out32(ADC_IRQ_ENABLE_SET(_adc_bank), 0x2);
}

void HeightSensor::sample() {
    out32(ADC_CTRL(_adc_bank), 0x1);
}

void HeightSensor::reset_interrupt() {
    out32(ADC_IRQ_STATUS(_adc_bank), 0x2);
}

float HeightSensor::convert_to_mm(int x) {
    float height_mm = 8.8347321472424051e+002;
    height_mm += -9.0520182685113570e-001 * x;
    height_mm += 3.1681822091607879e-004 * x * x;
    height_mm += -3.7026935208953069e-008 * x * x * x;
    return height_mm + _zero_point;
}

void HeightSensor::set_zero_point(int zero_point) {
    _zero_point = zero_point;
}

const int HeightSensor::get_value() {
    uint32_t data = in32(ADC_DATA(_adc_bank));
    return data;
}

HeightSensor::~HeightSensor() {

}
