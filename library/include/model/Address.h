#ifndef PARCELLOCKERS_ADDRESS_H
#define PARCELLOCKERS_ADDRESS_H

#include <string>
#include "exceptions/ClientException.h"

class Address{

private:
    std::string city;
    std::string street;
    int number;
public:
    Address(const std::string &city, const std::string &street, int number);

    virtual ~Address();

    std::string getAddressInfo()const;

    const std::string &getCity() const;

    const std::string &getStreet() const;

    int getNumber() const;
};



#endif //PARCELLOCKERS_ADDRESS_H
