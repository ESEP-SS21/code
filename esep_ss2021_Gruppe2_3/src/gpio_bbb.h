#ifndef GPIO_BBB_H
#define GPIO_BBB_H

namespace hal {

static constexpr uint32_t GPIO_SIZE = 0x1000;
// GPIO base adresses
static constexpr uint32_t GPIO_BASE_BANK0 = 0x44E07000;
static constexpr uint32_t GPIO_BASE_BANK1 = 0x4804C000;
static constexpr uint32_t GPIO_BASE_BANK2 = 0x481AC000;
// GPIO control register offsets
static constexpr uint32_t GPIO_OE = 0x134;
static constexpr uint32_t GPIO_DATAIN = 0x138;
static constexpr uint32_t GPIO_SETDATAOUT = 0x194;
static constexpr uint32_t GPIO_CLEARDATAOUT = 0x190;
static constexpr uint32_t GPIO_BANK0_MASK = 0x0CD0C0BC;
static constexpr uint32_t GPIO_BANK1_MASK = 0x000FF000;
static constexpr uint32_t GPIO_BANK2_MASK = 0x0000003C;

static constexpr uint32_t GPIO_IRQSTATUS_0 = 0x002C;
static constexpr uint32_t GPIO_IRQSTATUS_1 = 0x0030;
static constexpr uint32_t GPIO_IRQSTATUS_SET_0 = 0x0034;
static constexpr uint32_t GPIO_IRQSTATUS_SET_1 = 0x0038;
static constexpr uint32_t GPIO_IRQSTATUS_CLR_0 = 0x003C; //
static constexpr uint32_t GPIO_IRQSTATUS_CLR_1 = 0x0040;  //
static constexpr uint32_t GPIO_LEVELDETECT0 = 0x0140;
static constexpr uint32_t GPIO_LEVELDETECT1 = 0x0144;
static constexpr uint32_t GPIO_RAISINGDETECT = 0x0148;
static constexpr uint32_t GPIO_FALLINGDETECT = 0x14C;
static constexpr uint32_t GPIO_DEBOUNCENABLE = 0x150;
static constexpr uint32_t GPIO_DEBOUNCINGTIME = 0x154;

static constexpr uint32_t ADC_BASE = 0x44E0D000;
static constexpr uint32_t ADC_IRQ_ENABLE_SET = 0x2c;
static constexpr uint32_t ADC_IRQ_ENABLE_CLR = 0x30;
static constexpr uint32_t ADC_IRQ_STATUS = 0x28;
static constexpr uint32_t ADC_CTRL = 0x40;
static constexpr uint32_t ADC_DATA = 0x100;

// GPIO 0 bitmasks
static constexpr uint32_t LICHTSCHRANKE_EINLAUF_0 = 0x1 << 2;
static constexpr uint32_t LICHTSCHRANKE_HOEHENMESSUNG_0 = 0x1 << 3;
static constexpr uint32_t HOEHE_OK_0 = 0x1 << 4;
static constexpr uint32_t LICHTSCHRANKE_WEICHE_0 = 0x1 << 5;
static constexpr uint32_t METALLSENSOR_0 = 0x1 << 7;
static constexpr uint32_t WEICHE_OFFEN_0 = 0x1 << 14;
static constexpr uint32_t LICHTSCHRANKE_RUTSCHE_0 = 0x1 << 15;
static constexpr uint32_t LICHTSCHRANKE_AUSLAUF_0 = 0x1 << 20;
static constexpr uint32_t TASTE_START_0 = 0x1 << 22;
static constexpr uint32_t TASTE_STOP_0 = 0x1 << 23;
static constexpr uint32_t TASTE_RESET_0 = 0x1 << 26;
static constexpr uint32_t TASTE_ESTOPP_0 = 0x1 << 27;

// GPIO 1 bitmasks
static constexpr uint32_t MOTOR_RECHTS_1 = 0x1 << 12;
static constexpr uint32_t MOTOR_LINKS_1 = 0x1 << 13;
static constexpr uint32_t MOTOR_LANGSAM_1 = 0x1 << 14;
static constexpr uint32_t MOTOR_STOP_1 = 0x1 << 15;
static constexpr uint32_t AMPEL_ROT_1 = 0x1 << 16;
static constexpr uint32_t AMPEL_GELB_1 = 0x1 << 17;
static constexpr uint32_t AMPEL_GRUEN_1 = 0x1 << 18;
static constexpr uint32_t WEICHE_OEFFNEN_1 = 0x1 << 19;

// GPIO 2 bitmasks
static constexpr uint32_t LED_START_2 = 0x1 << 2;
static constexpr uint32_t LED_RESET_2 = 0x1 << 3;
static constexpr uint32_t LED_Q1_2 = 0x1 << 4;
static constexpr uint32_t LED_Q2_2 = 0x1 << 5;

}

#endif
