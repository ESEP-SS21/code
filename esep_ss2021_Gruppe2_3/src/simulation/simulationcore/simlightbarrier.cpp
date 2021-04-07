/* 
 * File:   simlightbarrier.cpp
 * @author Lehmann
 * @date 3. April 2020
 */

#include "simlightbarrier.h"
#include <cmath>
#include <iostream>

using namespace std;

SimLightBarrier::SimLightBarrier(vector<shared_ptr<SimItem> >* items, double position, SimulationIOImage* regs, unsigned short bitmask) : 
allitems(items), position(position), state(regs), bitmask(bitmask) {

}

void SimLightBarrier::evalTimeStep(unsigned int simTime){
    bool interrupted = false;  // true if interrupted
    
    for(const auto &it : (*allitems)){
        if(it->state==ItemState::onBelt){
            double rel_x = it->x - position;
            if(abs(rel_x)<=20.0){
                interrupted = true;
            }
            //cout << rel_x << ", " << interrupted << endl;
        }
    }
    setStateInImage(interrupted);
}

void    SimLightBarrier::setStateInImage(bool interrupted){
    if(interrupted){  // interrupted, -> active low
        state->in = (state->in & (~bitmask));
    }else{
        state->in = state->in | bitmask;
    }
    //cout << hex << state->in << dec << endl;  
};

SimLightBarrierSlide::SimLightBarrierSlide(vector<shared_ptr<SimItem> >* items, double position, SimulationIOImage* regs, unsigned short bitmask) :
SimLightBarrier(items, position, regs, bitmask){

}

void SimLightBarrierSlide::evalTimeStep(unsigned int simTime){
    bool interrupted = false;  // true if interrupted
    
    for(const auto &it : (*allitems)){
        if(it->state==ItemState::onSlide){
            double rel_y = it->y - position;
            if(abs(rel_y)<=20.0){
                interrupted = true;
            }
        }
    }
    setStateInImage(interrupted);
};

