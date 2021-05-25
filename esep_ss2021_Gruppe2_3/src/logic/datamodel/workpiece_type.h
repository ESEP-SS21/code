#pragma once

namespace logic {
namespace datamodel {


class WorkpieceType
{

public:
    enum Value {
        WRPC_HM = 0, WRPC_HB, WRPC_L,
        //^^^ need to be in sorting order^^^
        WRPC_H, // needs to be first in enum, which is to be discarded
        Unknown
    };

    constexpr static WorkpieceType first_in_order() { return WorkpieceType(Value::WRPC_HM); }
    constexpr static WorkpieceType first_not_in_order(){ return WorkpieceType(Value::WRPC_H); }

    constexpr bool is_to_be_discarded() const { return _value >= first_not_in_order()._value; }
    constexpr WorkpieceType next_in_sorting_order() {
        return WorkpieceType((_value + 1 ) % first_not_in_order()._value);
    }

    constexpr WorkpieceType() : _value(Value::Unknown) { }
    constexpr WorkpieceType(Value val) : _value(val) { }
    constexpr WorkpieceType(int val) : _value(static_cast<Value>(val)) { }

    constexpr bool operator==(WorkpieceType a) const { return _value == a._value; }
    constexpr bool operator!=(WorkpieceType a) const { return _value != a._value; }
    constexpr explicit operator int() const { return static_cast<int>(_value); }

private:
    Value _value;
};

} /* namespace datamodel */
} /* namespace logic*/
