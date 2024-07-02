#ifndef PARCELLOCKERS_CLIENTMANAGER_H
#define PARCELLOCKERS_CLIENTMANAGER_H
#include "repositories/ClientRepository.h"

class ClientManager {
private:
    ClientRepository repository;
public:

    ClientPtr registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID,
                             const AddressPtr &address);

    bool unregisterClient(const ClientPtr &client);

    std::vector<ClientPtr> findClients(ClientPredicate &predicate);

    std::vector<ClientPtr> findAllClients();

    ClientPtr getClientByID(const std::string& id) const;

};


#endif //PARCELLOCKERS_CLIENTMANAGER_H
