#ifndef SRC_HAL_H_
#define SRC_HAL_H_

#include "actuators/leds.h"
#include "actuators/sorting_mechanism.h"
#include "actuators/switch.h"
#include "actuators/ejector.h"
#include "actuators/cb_motor.h"
#include "actuators/stoplight.h"
#include "sensors/EStop.h"
#include "gpiowrapper.h"
#include "sensors/LightBarriers.h"
#include "sensors/HeightSensor.h"
#include "sensors/CPButtons.h"
#include "sensors/MetalSensor.h"

namespace hal {

class HAL {
private:
    std::shared_ptr<LEDs> _leds;
    std::shared_ptr<SortingMechanism> _sorting_mechanism;
    std::shared_ptr<CBMotor> _cb_motor;
    std::shared_ptr<Stoplight> _stoplight;
    std::shared_ptr<EStop> _estop;
    std::shared_ptr<LightBarriers> _light_barriers;
    std::shared_ptr<HeightSensor> _height_sensor;
    std::shared_ptr<CPButtons> _cp_buttons;
    std::shared_ptr<MetalSensor> _metal_sensor;

public:
    HAL(std::shared_ptr<GPIOWrapper>);
    ~HAL() = default;
    HAL(HAL const&) = delete;
    std::shared_ptr<LEDs> get_leds() const;
    std::shared_ptr<SortingMechanism> get_sorting_mechanism() const;
    std::shared_ptr<CBMotor> get_cb_motor() const;
    std::shared_ptr<Stoplight> get_stoplight() const;
    std::shared_ptr<EStop> get_estop() const;
    std::shared_ptr<LightBarriers> get_light_barriers() const;
    std::shared_ptr<HeightSensor> get_height_sensor() const;
    std::shared_ptr<CPButtons> get_cp_buttons() const;
    std::shared_ptr<MetalSensor> get_metal_sensor() const;

};

}

#endif /* SRC_HAL_H_ */
