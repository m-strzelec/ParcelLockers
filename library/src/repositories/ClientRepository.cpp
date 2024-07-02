#include "repositories/ClientRepository.h"

ClientPtr ClientRepository::findByPersonalId(const std::string & personalID) const {
    return findById<const std::string &>(personalID);
}