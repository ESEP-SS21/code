#include <memory>
#include <iostream>
#include "workpiece.h"


namespace logic {
namespace datamodel {

id Workpiece::_last_id = 0;

Workpiece::Workpiece() :
        _id(_last_id) {
    _last_id = (_last_id + 1) % (max_id);
}

Workpiece::Workpiece(EncodedWorkpiece encoded_wrpc) :
        _id(encoded_wrpc.get_id()),
        type(encoded_wrpc.get_type()),
        height_1(encoded_wrpc.get_height_1())
    {
    is_metallic = type == WorkpieceType::WRPC_HM;
}

bool Workpiece::operator==(const Workpiece& cmp) const {
    return this->_id == cmp.get_id();
}

WorkpieceType Workpiece::get_type() const{
    return type;
}


EncodedWorkpiece Workpiece::encode() const {
    return EncodedWorkpiece(this->_id | (height_1 << 21) | ((int) type << 30));
}

id Workpiece::get_id() const{
    return _id;
}

void Workpiece::determine_type() {
    if (height_2 == 0){
        this->type = determine_type_internal(height_1);
        return;
    }

    WorkpieceType new_type = determine_type_internal(height_2);
    if (this->type == new_type)
        return;

    this->is_flipped = true;
    //todo check for impossible flip
}

WorkpieceType Workpiece::determine_type_internal(int height) {
    if (height_is_within_tolerance(height_bohrung, height)) {
        return this->type = is_metallic ? WorkpieceType::WRPC_HM : WorkpieceType::WRPC_HB;
    }
    return
            height_is_within_tolerance(height_low, height) ? WorkpieceType::WRPC_L :
            height_is_within_tolerance(height_high, height) ?
                    WorkpieceType::WRPC_H : WorkpieceType::Unknown;
}

void Workpiece::print_wrpc_data() {
    std::cout << "--------------------------" << std::endl;
    std::cout << "Workpiece " << this->get_id() << std::endl;
    print_type_str();
    std::cout << "Height 1: " << ((float)this->height_1)/10 << " mm" <<std::endl;
    std::cout << "Height 2: " << ((float)this->height_2)/10 << " mm"<<std::endl;
    std::cout << "Metallic: " << this->is_metallic << std::endl;
    std::cout << "Flipped: " << this->is_flipped << std::endl;
    std::cout << "--------------------------" << std::endl;
}

void Workpiece::print_type_str() {
    std::cout << "Type: "<<
    (this->get_type() == WorkpieceType::WRPC_HM ? "WRPC_HM" :
    this->get_type() == WorkpieceType::WRPC_HB ? "WRPC_HB" :
    this->get_type() == WorkpieceType::WRPC_L ? "WRPC_L" :
    this->get_type() == WorkpieceType::WRPC_H ? "WRPC_H" : "UNKNOWN") << std::endl;
}

} /* namespace datamodel */
} /* namespace logic*/

