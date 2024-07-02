#include "model/Address.h"
#include <sstream>

Address::Address(const std::string &city, const std::string &street, int number)
    : city(city), street(street), number(number) {
    if (city.empty()) throw ClientException("Address instantiation error: city value must not be an empty string.");
    this->city = city;
}

Address::~Address() = default;

std::string Address::getAddressInfo()const {
    std::stringstream chain;
    chain<<"city: "<<city<<" street: "<<street<<" number: "<<std::to_string(number);
    return chain.str();
}
const std::string &Address::getCity() const {
    return city;
}

const std::string &Address::getStreet() const {
    return street;
}

int Address::getNumber() const {
    return number;
}

