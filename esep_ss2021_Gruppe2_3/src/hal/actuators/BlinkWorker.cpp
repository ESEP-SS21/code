#include "../actuators/BlinkWorker.h"
#include <iostream>
#include <memory>

namespace hal {

using namespace dispatcher;

BlinkWorker::BlinkWorker(std::shared_ptr<GPIOWrapper> gpio) :
        _gpio { gpio }, _running { true }, _duty_cycle { 1000 }, _color { hal::RED }, _interrupted{true} {
}

void BlinkWorker::run() {
    int val = 0;
    while (_running) {
        std::unique_lock<std::mutex> lk(_mutex);
        while(_interrupted){
            _cv.wait(lk);
        }
        val = !val;
        switch (_color) {
        case GREEN:
            _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, val);
            break;
        case YELLOW:
            _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, val);
            break;
        default:
            _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, val);
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(_duty_cycle / 2));
    }
}

void BlinkWorker::stop_loop() {
    stop_blinking();
    _interrupted = false;
    _cv.notify_all();
    _running = false;
}

void BlinkWorker::set_duty_cycle(const uint32_t milliseconds) {
    _duty_cycle = milliseconds;
}

void BlinkWorker::start_blinking(Color c) {
    _color = c;
    _interrupted = false;
    _cv.notify_all();
    _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
    _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
    _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
}

void BlinkWorker::stop_blinking() {
     _interrupted = true;
     _cv.notify_all();
    _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GRUEN_1, 0);
    _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_GELB_1, 0);
    _gpio->out(gpio_adresses::BANK_ACTUATOR, gpio_adresses::AMPEL_ROT_1, 0);
}

BlinkWorker::~BlinkWorker() {
    _running = false;
    _interrupted = false;
    _cv.notify_all();
}

} /* namespace hal */
