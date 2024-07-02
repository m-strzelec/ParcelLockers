#include "model/Standard.h"
#include <sstream>

Standard::Standard(int id, double mass, bool isSent, int basePrice) : Parcel(id, mass, isSent, basePrice) {}

Standard::~Standard() = default;

double Standard::getActualSendPrice() {
    return Parcel::getActualSendPrice();
}
std::string Standard::getParcelInfo() {
    std::stringstream chain;
    chain<<"Standard Parcel: "<<Parcel::getParcelInfo();
    return chain.str();
}
