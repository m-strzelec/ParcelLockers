#ifndef PARCELLOCKERS_CLIENTREPOSITORY_H
#define PARCELLOCKERS_CLIENTREPOSITORY_H

#include "model/Client.h"
#include "repositories/Repository.h"
#include "typedefs.h"
#include <vector>
#include <string>
#include <stdexcept>

class ClientRepository : public Repository<Client> {
public:
    ClientPtr findByPersonalId(const std::string &personalID) const;
};


#endif //PARCELLOCKERS_CLIENTREPOSITORY_H
