#pragma once

#include <cstdint>
#include <memory>
#include <sys/neutrino.h>
#include "simqnxirqapi.h"
#include "simqnxgpioapi.h"

#define ADC_IRQ_ENABLE_SET(base) (uintptr_t)base + 0x2c
#define ADC_IRQ_ENABLE_CLR(base) (uintptr_t)base + 0x30
#define ADC_IRQ_STATUS(base) (uintptr_t)base + 0x28
#define ADC_CTRL(base) (uintptr_t)base + 0x40
#define ADC_DATA(base) (uintptr_t)base + 0x100

#define ADC_START_ADDRESS 0x44E0D000
#define ADC_ADDRESS_LENGTH 0x2000

class HeightSensor {
private:
    uintptr_t _adc_bank;
    int _zero_point;
public:
    HeightSensor();
    virtual ~HeightSensor();
    void sample();
    void reset_interrupt();
    float convert_to_mm(int);
    void set_zero_point(int);
    const int get_value();
};

