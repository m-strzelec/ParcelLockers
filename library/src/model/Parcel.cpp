#include <string>
#include "model/Parcel.h"
#include <sstream>

Parcel::Parcel(int id, double mass, bool InLocker, int basePrice) : id(id), mass(mass), inLocker(InLocker),
                                                                    basePrice(basePrice) {

    if (id==0) throw ParcelException("Parcel instantiation error: id must be assigned.");
    if (basePrice <=0) throw ParcelException ("Parcel instantiation error: basePrice must be a positive value.");
    if (mass <=0) throw ParcelException ("Parcel instantiation error: mass must be a positive value");
}

Parcel::~Parcel() = default;

double Parcel::getActualSendPrice() {
    return getBasePrice()*getMass();
}

std::string Parcel::getParcelInfo() {
    std::stringstream chain;
    chain<<"Id: "<<id<<" Mass: "<<mass;
    return chain.str();
}

std::string Parcel::getInfo() {
    return getParcelInfo();
}

int Parcel::getId() const {
    return id;
}

double Parcel::getMass() const {
    return mass;
}

bool Parcel::isInLocker() const {
    return inLocker;
}

int Parcel::getBasePrice() const {
    return basePrice;
}

void Parcel::setIsInLocker(bool IsInLocker) {
    inLocker = IsInLocker;
}
