/*
 * HeightSensor.h
 *
 *  Created on: 13.05.2021
 *      Author: Lasse
 */

#ifndef SRC_HAL_SENSORS_HEIGHTSENSOR_H_
#define SRC_HAL_SENSORS_HEIGHTSENSOR_H_

class HeightSensor {
private:
    char _event_number;
    int _zero_point;
    float _scaling_factor;
public:
    HeightSensor(int);
    virtual ~HeightSensor();
    void sample();
    float convert_to_mm(int);
    void set_zero_point();
    char get_event_number();
};

#endif /* SRC_HAL_SENSORS_HEIGHTSENSOR_H_ */
