#ifndef PARCELLOCKERS_CLIENT_H
#define PARCELLOCKERS_CLIENT_H

#include "Address.h"
#include "exceptions/ClientException.h"
#include "typedefs.h"
#include <string>
#include <vector>


class Client{

private:
    std::string firstName;
    std::string lastName;
    std::string personalID;
    AddressPtr address;
public:
    Client(const std::string &firstName, const std::string &lastName, const std::string &personalID,
           const AddressPtr &address);

    ~Client();

    std::string getClientInfo() const;

    std::string getInfo() const;

    const std::string &getFirstName() const;

    const std::string &getLastName() const;

    const std::string &getPersonalID() const;

    const std::string &getId() const;

    AddressPtr getAddress() const;


};


#endif //PARCELLOCKERS_CLIENT_H
