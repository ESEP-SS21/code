#pragma once

#include <map>
#include <iostream>
#include <sstream>

#include "cnnMngmnt/namespacedata.h"

namespace dispatcher {

#define EVNT_PREFIX "EVNT_"

enum class EventType { //make sure to add a string representation for each value
    EVNT_ERR = 0,
    EVNT_ERR_GONE,
    EVNT_WRN,
    EVNT_WRN_GONE,
    EVNT_HRTB,
    EVNT_ACK,
    EVNT_SEN_LB_ST_BLCK,
    EVNT_SEN_LB_ST_CLR,
    EVNT_SEN_LB_SW_BLCK,
    EVNT_SEN_LB_SW_CLR,
    EVNT_SEN_LB_RA_BLCK,
    EVNT_SEN_LB_RA_CLR,
    EVNT_SEN_LB_EN_BLCK,
    EVNT_SEN_LB_EN_CLR,
    EVNT_SEN_LB_HE_BLCK,
    EVNT_SEN_LB_HE_CLR,
    EVNT_SEN_METAL_DTC,
    EVNT_SEN_HEIGHT_REQ,
    EVNT_SEN_HEIGHT_HE,
    EVNT_SEN_ESTOP_ON,
    EVNT_SEN_ESTOP_OFF,
    EVNT_CTRL_T_STR_PRS_LNG,
    EVNT_CTRL_T_STR_PRS_SRT,
    EVNT_CTRL_T_STP_PRS_LNG,
    EVNT_CTRL_T_STP_PRS_SRT,
    EVNT_CTRL_T_RST_PRS_LNG,
    EVNT_CTRL_T_RST_PRS_SRT,
    EVNT_ACT_CTRL_T_STR_LED_ON,
    EVNT_ACT_CTRL_T_STR_LED_OFF,
    EVNT_ACT_CTRL_T_RST_LED_ON,
    EVNT_ACT_CTRL_T_RST_LED_OFF,
    EVNT_ACT_BELT_BWD,
    EVNT_ACT_BELT_FWD,
    EVNT_ACT_BELT_STP,
    EVNT_ACT_SORT_DSC,
    EVNT_ACT_SORT_NO_DSC,
    EVNT_ACT_SORT_RST,
    EVNT_ACT_STPL_LED_ON,
    EVNT_ACT_STPL_LED_OFF,
    EVNT_ACT_STPL_LED_BLNK_FST,
    EVNT_ACT_STPL_LED_BLNK_SLW,
    EVNT_WRPC_TRNS_RQ,
    EVNT_WRPC_FLP,
    EVNT_MOD_IDL,
    EVNT_MOD_OP,
    EVNT_MOD_ERR,
    EVNT_TIM_REQ,
    EVNT_TIM_ALRT,
    EVNT_CONN_LOST,
    SIZE = 64
};

enum class TimerID
    :uint16_t {
        HEARTBEAT, SORT_WRPC_STUCK, SORT_WRPC_FULL, WRPC_TRANSFER_BLOCKED,
};

inline std::ostream& operator<<(std::ostream& out, const EventType& e) {
    static const std::string strs[static_cast<int>(EventType::SIZE) + 1] = {
            "EVNT_ERR",
            "EVNT_ERR_GONE",
            "EVNT_WRN",
            "EVNT_WRN_GONE",
            "EVNT_HRTB",
            "EVNT_ACK",
            "EVNT_SEN_LB_ST_BLCK",
            "EVNT_SEN_LB_ST_CLR",
            "EVNT_SEN_LB_SW_BLCK",
            "EVNT_SEN_LB_SW_CLR",
            "EVNT_SEN_LB_RA_BLCK",
            "EVNT_SEN_LB_RA_CLR",
            "EVNT_SEN_LB_EN_BLCK",
            "EVNT_SEN_LB_EN_CLR",
            "EVNT_SEN_LB_HE_BLCK",
            "EVNT_SEN_LB_HE_CLR",
            "EVNT_SEN_METAL_DTC",
            "EVNT_SEN_HEIGHT_REQ",
            "EVNT_SEN_HEIGHT_HE",
            "EVNT_SEN_ESTOP_ON",
            "EVNT_SEN_ESTOP_OFF",
            "EVNT_CTRL_T_STR_PRS_LNG",
            "EVNT_CTRL_T_STR_PRS_SRT",
            "EVNT_CTRL_T_STP_PRS_LNG",
            "EVNT_CTRL_T_STP_PRS_SRT",
            "EVNT_CTRL_T_RST_PRS_LNG",
            "EVNT_CTRL_T_RST_PRS_SRT",
            "EVNT_ACT_CTRL_T_STR_LED_ON",
            "EVNT_ACT_CTRL_T_STR_LED_OFF",
            "EVNT_ACT_CTRL_T_RST_LED_ON",
            "EVNT_ACT_CTRL_T_RST_LED_OFF",
            "EVNT_ACT_BELT_BWD",
            "EVNT_ACT_BELT_FWD",
            "EVNT_ACT_BELT_STP",
            "EVNT_ACT_SORT_DSC",
            "EVNT_ACT_SORT_NO_DSC",
            "EVNT_ACT_SORT_RST",
            "EVNT_ACT_STPL_LED_ON",
            "EVNT_ACT_STPL_LED_OFF",
            "EVNT_ACT_STPL_LED_BLNK_FST",
            "EVNT_ACT_STPL_LED_BLNK_SLW",
            "EVNT_WRPC_TRNS_RQ",
            "EVNT_WRPC_FLP",
            "EVNT_MOD_IDL",
            "EVNT_MOD_OP",
            "EVNT_MOD_ERR",
            "EVNT_TIM_REQ",
            "EVNT_TIM_ALRT",
            "EVNT_CONN_LOST",

    };
    return out << EVNT_PREFIX << strs[static_cast<int>(e)];
}


inline std::string str(EventType et) {
    std::ostringstream buffer;
    buffer << et;
    return buffer.str();
}

struct Event {
    EventType type;
    int payload;
    bool broadcast;

    Event(EventType type, int payload, bool broadcast) :
            type(type), payload(payload), broadcast(broadcast) {
    }

    Event(const cnnMngmnt::custom_header_t& header) :
            payload(header.value.sival_int), broadcast(false) {

        int evnt_id = header.code;
        if (transmission_bit_set(evnt_id)) {
            broadcast = true;
            evnt_id = mask_out_tranmission_bit(evnt_id);
        }
        type = EventType(evnt_id);
    }

    std::string str() {
        std::ostringstream buffer;
        buffer << type << " payload: " << payload;
        return buffer.str();
    }

    bool operator== (const Event& e) const{
        return e.type == type && e.payload == payload;
    }

    bool operator!= (const Event& e) const{
        return !(*this == e);
    }

    static inline Event CreateTimer(TimerID id, uint16_t time_ms, bool broadcast = false) {
        return Event { dispatcher::EventType::EVNT_TIM_REQ, (static_cast<uint16_t>(id) << 16) + time_ms, broadcast };
    }

private:
    bool transmission_bit_set(int evnt_id) {
        return (evnt_id & 0b01000000) != 0;
    }

    int mask_out_tranmission_bit(int evnt_id) {
        return evnt_id & (~0b01000000);
    }


};

struct EventSubscription {
    EventType type;
    cnnMngmnt::chid chid;
};

} /* namespace dispatcher */
