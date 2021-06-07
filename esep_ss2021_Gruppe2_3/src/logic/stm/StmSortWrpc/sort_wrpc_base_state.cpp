#include "sort_wrpc_base_state.h"
#include "states/operating_substates/WaitingForWrpc.h"
#include "states/wfstc_substates/NoDiscard.h"

void logic::stm::sortWrpcStm::SortWrpcBaseState::init_sub_states() {
    _operating_substate = new WaitingForWrpc;
    _operating_substate->SetData(_eventSender, _datamodel);

    _wfstc_substate = new NoDiscard;
    _wfstc_substate->SetData(_eventSender, _datamodel);
}
