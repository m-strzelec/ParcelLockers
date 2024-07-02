#include "model/Carefull.h"
#include <sstream>

Carefull::Carefull(int id, double mass, bool isSent, int basePrice, SegmentType segment)
    : Parcel(id, mass, isSent, basePrice), segment(segment) {}

Carefull::~Carefull() = default;

double Carefull::getActualSendPrice() {
    return Parcel::getActualSendPrice()+getMass()*getSegment()/10;
}

std::string Carefull::getParcelInfo() {
    std::stringstream chain;
    chain<<"Carefull Parcel: "<<Parcel::getParcelInfo()<<" Type: "<<getSegment();
    return chain.str();
}

SegmentType Carefull::getSegment() const {
    return segment;
}

