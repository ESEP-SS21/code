#include <iostream>
#include <sys/mman.h>
#include "gpiowrapper.h"


namespace hal {

GPIOWrapper::GPIOWrapper() {
    _bank_input = mmap_device_io(gpio_adresses::GPIO_SIZE,
            (uint64_t ) gpio_adresses::GPIO_BASE_BANK0);
    _bank_actuator = mmap_device_io(gpio_adresses::GPIO_SIZE,
            (uint64_t ) gpio_adresses::GPIO_BASE_BANK1);
    _bank_led = mmap_device_io(gpio_adresses::GPIO_SIZE,
            (uint64_t ) gpio_adresses::GPIO_BASE_BANK2);
    out32((uintptr_t ) (_bank_input + gpio_adresses::GPIO_OE), 0xFFFFFFFF); //set all pins to input
    out32((uintptr_t ) (_bank_actuator + gpio_adresses::GPIO_OE), 0x00000000); //set all pins to input
    out32((uintptr_t ) (_bank_led + gpio_adresses::GPIO_OE), 0x00000000); //set all pins to input
    write_value_to_register(gpio_adresses::BANK_LED, gpio_adresses::GPIO_CLEARDATAOUT ,0xFFFFFFFF);
    write_value_to_register(gpio_adresses::BANK_ACTUATOR, gpio_adresses::GPIO_CLEARDATAOUT ,0xFFFFFFFF);
}

GPIOWrapper::~GPIOWrapper() {
    write_value_to_register(gpio_adresses::BANK_LED, gpio_adresses::GPIO_CLEARDATAOUT ,0xFFFFFFFF);
    write_value_to_register(gpio_adresses::BANK_ACTUATOR, gpio_adresses::GPIO_CLEARDATAOUT ,0xFFFFFFFF);
    // wait for sim to tick, not needed on real hardware
    usleep(1000*10);
    munmap_device_io(_bank_input, gpio_adresses::GPIO_SIZE);
    munmap_device_io(_bank_actuator, gpio_adresses::GPIO_SIZE);
    munmap_device_io(_bank_led, gpio_adresses::GPIO_SIZE);
}

void GPIOWrapper::out(uint32_t bank, uint32_t pin, uint32_t value) {
    if (value) {
        set_bit_in_register(bank, gpio_adresses::GPIO_SETDATAOUT, pin);
    } else {
        set_bit_in_register(bank, gpio_adresses::GPIO_CLEARDATAOUT, pin);
    }
}

const uint32_t GPIOWrapper::in(uint32_t bank, uint32_t pin) {
    return read_value_from_register(bank, gpio_adresses::GPIO_DATAIN, pin);
}

void GPIOWrapper::enable_interrupt(uint32_t bank, uint32_t pin) {
    set_bit_in_register(bank, gpio_adresses::GPIO_IRQSTATUS_SET_1, pin);
}

void GPIOWrapper::disable_interrupt(uint32_t bank, uint32_t pin) {
    set_bit_in_register(bank, gpio_adresses::GPIO_IRQSTATUS_SET_0, pin);
}

void GPIOWrapper::enable_debounce(uint32_t bank, uint32_t pin) {
    add_bit_to_register(bank, gpio_adresses::GPIO_DEBOUNCENABLE, pin);
}

void GPIOWrapper::set_debounce_time(uint32_t bank, uint32_t time_ms) {
    write_value_to_register(bank, gpio_adresses::GPIO_DEBOUNCENABLE, time_ms);
}

void GPIOWrapper::enable_interrupt_falling(uint32_t bank, uint32_t pin) {
    add_bit_to_register(bank, gpio_adresses::GPIO_FALLINGDETECT, pin);
}

void GPIOWrapper::enable_interrupt_rising(uint32_t bank, uint32_t pin) {
    add_bit_to_register(bank, gpio_adresses::GPIO_RAISINGDETECT, pin);
}

void GPIOWrapper::reset_interrupt(){
    // before reset we want to read the iir register
    uint32_t iir = in32(_bank_input+gpio_adresses::GPIO_IRQSTATUS_1);
    // reset irq register
    out32(_bank_input+gpio_adresses::GPIO_IRQSTATUS_1, iir);
}

// Sets a single bit in a register and erases the other ones
void GPIOWrapper::set_bit_in_register(uint32_t bank, const uint32_t gpio_register,
        uint32_t pin) const {
    switch (bank) {
    case 0: {
        out32((uintptr_t ) (_bank_input + gpio_register), 0x1 << (pin));
        break;
    }
    case 1: {
        out32((uintptr_t ) (_bank_actuator + gpio_register), 0x1 << (pin));
        break;
    }
    case 2: {
        out32((uintptr_t ) (_bank_led + gpio_register), 0x1 << (pin));
        break;
    }
    default:
        std::cout << "GPIOWrapper " << bank << "not valid\n";
    }
}

// sets a single bit in a register without touching the others
void GPIOWrapper::add_bit_to_register(uint32_t bank, const uint32_t gpio_register,
        uint32_t pin) const {
    switch (bank) {
    case 0: {
        uint32_t old = in32((uintptr_t ) (_bank_input + gpio_register));
        out32((uintptr_t ) (_bank_input + gpio_register), old | (0x1 << (pin)));
        break;
    }
    case 1: {
        uint32_t old = in32((uintptr_t ) (_bank_actuator + gpio_register));
        out32((uintptr_t ) (_bank_actuator + gpio_register), old | (0x1 << (pin)));
        break;
    }
    case 2: {
        uint32_t old = in32((uintptr_t ) (_bank_led + gpio_register));
        out32((uintptr_t ) (_bank_led + gpio_register), old | (0x1 << (pin)));
        break;
    }
    default:
        std::cout << "GPIOWrapper " << bank << "not valid\n";
    }
}

void GPIOWrapper::write_value_to_register(uint32_t bank, const uint32_t gpio_register,
        uint32_t value) const {
    switch (bank) {
    case 0:
        out32((uintptr_t ) (_bank_input + gpio_register), value);
        break;
    case 1:
        out32((uintptr_t ) (_bank_actuator + gpio_register), value);
        break;
    case 2:
        out32((uintptr_t ) (_bank_led + gpio_register), value);
        break;
    default:
        std::cout << "GPIOWrapper " << bank << "not valid\n";
    }
}

uint32_t GPIOWrapper::read_value_from_register(uint32_t bank, const uint32_t gpio_register,
        uint32_t pin) const {
    switch (bank) {
    case 0:
        return (in32((uintptr_t ) (_bank_input + gpio_register)) & (0x1 << (pin))) >> (pin);
        break;
    case 1:
        return (in32((uintptr_t ) (_bank_actuator + gpio_register)) & (0x1 << (pin))) >> (pin);
        break;
    case 2:
        return (in32((uintptr_t)(_bank_led + gpio_register)) & (0x1 << (pin))) >> (pin);
        break;
    default:
        return -1;
    }
}

}

