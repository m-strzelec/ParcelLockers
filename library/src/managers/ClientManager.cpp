#include "managers/ClientManager.h"
#include <memory>
#include <utility>
ClientPtr
ClientManager::registerClient(const std::string &firstName, const std::string &lastName, const std::string &personalID,
                              const AddressPtr &address){

    ClientPtr c = getClientByID(personalID);
    if(c == nullptr)
    {
        c = std::make_shared<Client>(firstName, lastName,personalID,address);
        repository.addObject(c);
    }
    return c;
}

ClientPtr ClientManager::getClientByID(const std::string &id) const {
    return repository.findById(id);
}

// metoda unregister sluzy do usuwania rejestru
bool ClientManager::unregisterClient(const ClientPtr &client) {
    ClientPtr c = getClientByID(client->getPersonalID());
    if(c != nullptr) {
        repository.removeObject(c);
        return true;
    }
    return false;
}

std::vector<ClientPtr> ClientManager::findClients(ClientPredicate &predicate) {
    return repository.findBy(std::move(predicate));
}

std::vector<ClientPtr> ClientManager::findAllClients() {
    return repository.findAll();
}