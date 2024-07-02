#ifndef PARCELLOCKERS_STORAGECONTAINER_H
#define PARCELLOCKERS_STORAGECONTAINER_H
#include "ClientRepository.h"
#include "OrderRepository.h"
#include "ParcelRepository.h"

class StorageContainer{
private:
    ClientRepository clientrepo;
    OrderRepository orderrepo;
    ParcelRepository parcelrepo;
public:
    StorageContainer();

    ClientRepository &getClientrepo() ;

    OrderRepository &getOrderrepo() ;

    ParcelRepository &getParcelrepo() ;
};
#endif //PARCELLOCKERS_STORAGECONTAINER_H
