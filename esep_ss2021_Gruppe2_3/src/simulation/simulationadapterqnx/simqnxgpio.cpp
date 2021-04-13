/*
 * simgpio.cpp
 *
 *  Created on: 09.04.2020
 *      Author: Lehmann
 */

#include <iostream>

#include "simqnxgpio.h"
using namespace std;

void SimGPIO::simOut32(unsigned int addr, unsigned int value) {
	//cout << "<SIM out32>" << hex << addr << ", " << value << dec << endl;
	unsigned int setvalue = 0;

	switch (addr) {
	case SIMGPIO_BASE_BANK0 + SIMGPIO_OE:
		bank0_OE = value;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_0:
		bank0_IRQSTATUS_0 = bank0_IRQSTATUS_0 & (~value);
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_SET_0:
		bank0_IRQSTATUS_ENABLE_0 = bank0_IRQSTATUS_ENABLE_0 | value;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_CLR_0:
		bank0_IRQSTATUS_ENABLE_0 = bank0_IRQSTATUS_ENABLE_0 & (~value);
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_1:
		bank0_IRQSTATUS_1 = bank0_IRQSTATUS_1 & (~value);
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_SET_1:
		bank0_IRQSTATUS_ENABLE_1 = bank0_IRQSTATUS_ENABLE_1 | value;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_CLR_1:
		bank0_IRQSTATUS_ENABLE_1 = bank0_IRQSTATUS_ENABLE_1 & (~value);
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_LEVELDETECT0:
		bank0_LEVELDETECT0 = value;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_LEVELDETECT1:
		bank0_LEVELDETECT1 = value;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_RAISINGDETECT:
		bank0_RAISINGDETECT = value;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_FALLINGDETECT:
		bank0_FALLINGDETECT = value;
		break;
	case SIMGPIO_BASE_BANK1 + SIMGPIO_OE:
		bank1_OE = value;
		break;
	case SIMGPIO_BASE_BANK2 + SIMGPIO_OE:
		bank2_OE = value;
		break;
	case SIMGPIO_BASE_BANK1 + SIMGPIO_CLEARDATAOUT:
		//cout << "bank1 set out:" << hex << value << dec << endl;
		value = value & ~bank1_OE;
		//cout << "set out enabled:" << hex << value << dec << endl;
		setvalue = simulation->readOut();
		setvalue = setvalue & ~((value & SIMGPIO_BANK1_MASK) >> 12);
		//cout << "set:" << hex << setvalue << dec << endl;
		simulation->writeOut(setvalue);
		break;
	case SIMGPIO_BASE_BANK1 + SIMGPIO_SETDATAOUT:
		//cout << "bank1 set out:" << hex << value << dec << endl;
		value = value & ~bank1_OE;
		//cout << "set out enabled:" << hex << value << dec << endl;
		setvalue = simulation->readOut();
		setvalue = setvalue | ((value & SIMGPIO_BANK1_MASK) >> 12);
		//cout << "set:" << hex << setvalue << dec << endl;
		simulation->writeOut(setvalue);
		break;
	case SIMGPIO_BASE_BANK2 + SIMGPIO_CLEARDATAOUT:
		//cout << "bank2 set out:" << hex << value << dec << endl;
		value = value & ~bank2_OE;
		//cout << "set out enabled:" << hex << value << dec << endl;
		setvalue = simulation->readOut();
		setvalue = setvalue & ~((value & SIMGPIO_BANK2_MASK)<<6);
		//cout << "set:" << hex << setvalue << dec << endl;
		simulation->writeOut(setvalue);
		break;
	case SIMGPIO_BASE_BANK2 + SIMGPIO_SETDATAOUT:
		//cout << "bank2 set out:" << hex << value << dec << endl;
		value = value & ~bank2_OE;
		//cout << "set out enabled:" << hex << value << dec << endl;
		setvalue = simulation->readOut();
		setvalue = setvalue | ((value & SIMGPIO_BANK2_MASK)<<6);
		//cout << "set:" << hex << setvalue << dec << endl;
		simulation->writeOut(setvalue);
		break;
	case SIMADC_BASE + SIMADC_IRQ_ENABLE_SET:
		adc_irq_enable = adc_irq_enable | (value & 0x02);
		break;
	case SIMADC_BASE + SIMADC_IRQ_ENABLE_CLR:
		adc_irq_enable = adc_irq_enable & (~(value & 0x02));
		break;
	case SIMADC_BASE + SIMADC_IRQ_STATUS:
		adc_irq_status = adc_irq_status & (~(value & 0x02));
		break;
	case SIMADC_BASE + SIMADC_CTRL:
		adc_ctrl = value & 0x01;
		break;
	}
}

unsigned int SimGPIO::simIn32(unsigned int addr) {
	unsigned int result = 0;
	unsigned int inreg = 0;
	switch (addr) {
	case SIMGPIO_BASE_BANK0 + SIMGPIO_OE:
		result = bank0_OE;
		break;
	case SIMGPIO_BASE_BANK1 + SIMGPIO_OE:
		result = bank1_OE;
		break;
	case SIMGPIO_BASE_BANK2 + SIMGPIO_OE:
		result = bank2_OE;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_0:
		result = bank0_IRQSTATUS_0;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_SET_0:
		result = bank0_IRQSTATUS_ENABLE_0;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_CLR_0:
		result = bank0_IRQSTATUS_ENABLE_0;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_1:
		result = bank0_IRQSTATUS_1;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_SET_1:
		result = bank0_IRQSTATUS_ENABLE_1;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_IRQSTATUS_CLR_1:
		result = bank0_IRQSTATUS_ENABLE_1;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_LEVELDETECT0:
		result = bank0_LEVELDETECT0;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_LEVELDETECT1:
		result = bank0_LEVELDETECT1;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_RAISINGDETECT:
		result = bank0_RAISINGDETECT;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_FALLINGDETECT:
		result = bank0_FALLINGDETECT;
		break;
	case SIMGPIO_BASE_BANK0 + SIMGPIO_DATAIN:
		inreg = simulation->readIn();
		result = (inreg & 0x0000000F) << 2;
		result = result | (inreg & 0x00000010) << 3;
		result = result | (inreg & 0x00000060) << 9;
		result = result | (inreg & 0x00000080) << 13;
		result = result | (inreg & 0x00000300) << 14;
		result = result | (inreg & 0x00000C00) << 16;
		result = result & SIMGPIO_BANK0_MASK;
		break;
	case SIMGPIO_BASE_BANK1 + SIMGPIO_DATAIN:
		result = simulation->readOut();
		result = (result << 12) & SIMGPIO_BANK1_MASK;
		break;
	case SIMGPIO_BASE_BANK2 + SIMGPIO_DATAIN:
		result = simulation->readOut();
		result = result & SIMGPIO_BANK2_MASK;
		break;
	case SIMADC_BASE + SIMADC_IRQ_ENABLE_SET:
		result = adc_irq_enable;
		break;
	case SIMADC_BASE + SIMADC_IRQ_STATUS:
		result = adc_irq_status;
		break;
	case SIMADC_BASE + SIMADC_CTRL:
		result = adc_ctrl;
		break;
	case SIMADC_BASE + SIMADC_DATA:
		result = adc_data;
		break;
	}
	return result;
}

// sensorin is 12 bit input image
// check against value of last call
bool SimGPIO::checkRasingIRQGPIO(unsigned int sensorin) {
	unsigned int result = 0;
	unsigned int raise = 0;

	result = (sensorin & 0x0000000F) << 2;
	result = result | (sensorin & 0x00000010) << 3;
	result = result | (sensorin & 0x00000060) << 9;
	result = result | (sensorin & 0x00000080) << 13;
	result = result | (sensorin & 0x00000300) << 14;
	result = result | (sensorin & 0x00000C00) << 16;

	{
		std::lock_guard<std::mutex> lk(irqregmutex);
		// check raising
		unsigned int raising = (result ^ lastSensorIn) & result;
		raising = raising & bank0_RAISINGDETECT;
		// check faling
		unsigned int falling = (result ^ lastSensorIn) & lastSensorIn;
		falling = falling & bank0_FALLINGDETECT;

		// raising or falling, not irq_status 1 -> raise interrupt
		// spruh73l, p4884
		raise = (raising | falling) & ~bank0_IRQSTATUS_1 & bank0_IRQSTATUS_ENABLE_1;
		bank0_IRQSTATUS_1 |= raise;

		lastSensorIn = result;
	}
	return (raise != 0);
}

bool SimGPIO::checkRasingIRQADC(){
	return (adc_irq_status == 0x02);
};

void SimGPIO::updateDataADC(unsigned int rawvalue){
	// irq enabled and sampling requested and no old irq pending
	if((adc_irq_enable == 0x02) && (adc_ctrl == 0x01) && (adc_irq_status == 0x00) ){
		adc_data = rawvalue;
		adc_ctrl = adc_ctrl & (~0x01);   // auto clear sampling flag
		adc_irq_status = adc_irq_status | 0x02;  // raise IRQ
	}
}

uint32_t simqnx_In32(uintptr_t addr) {
	return SimGPIO::getGPIO()->simIn32(addr);
}

void simqnx_Out32(uintptr_t addr, uint32_t value) {
	SimGPIO::getGPIO()->simOut32(addr, value);
}

uintptr_t simqnx_mmap_device_io(size_t len, uint64_t io) {
//	cout << "mmap" << hex << io << dec << endl;
	return io;
}

