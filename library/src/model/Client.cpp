#include "model/Client.h"

Client::Client(const std::string &firstName, const std::string &lastName, const std::string &personalID, const AddressPtr &address)
    : firstName(firstName), lastName(lastName), personalID(personalID), address(address) {
    if (personalID.empty()) throw ClientException("Client instantiation error: PID must not be empty.");
    if (address == nullptr) throw ClientException("Client instantiation error: Address must not be a nullptr.");
}

Client::~Client() = default;

std::string Client::getClientInfo() const {
    return "personalID: " + personalID + "  " + firstName+ "  " + lastName+ ", adres: " + address->getAddressInfo();
}

std::string Client::getInfo() const {
    return getClientInfo();
}

const std::string &Client::getFirstName() const {
    return firstName;
}

const std::string &Client::getLastName() const {
    return lastName;
}

const std::string &Client::getPersonalID() const {
    return personalID;
}

const std::string &Client::getId() const {
    return getPersonalID();
}

AddressPtr Client::getAddress() const {
    return address;
}
