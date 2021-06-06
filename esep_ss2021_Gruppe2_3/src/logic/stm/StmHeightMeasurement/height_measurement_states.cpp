#include <logic/stm/StmHeightMeasurement/height_measurement_states.h>

namespace logic {
namespace stm {
namespace StmHeightMeasurement {

STATE_INIT(WaitingForWorkpiece)

bool WaitingForWorkpiece::lb_he_blck(){
    return false;
}

bool WaitingForHeight::he_sensor_he(payload){
    return false;
}

bool WorkpiecePrimary::lb_he_clr(){
    return false;
}

bool WorkpieceSecondary::lb_he_clr(){
    return false;
}
