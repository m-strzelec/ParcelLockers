#include "managers/ParcelManager.h"


std::vector<ParcelPtr> ParcelManager::findParcel(const ParcelPredicate& predicate) {
    return repository.findBy(predicate);
}

std::vector<ParcelPtr> ParcelManager::findAllParcels() {
    return repository.findAll();
}

ParcelPtr ParcelManager::getParcelById(const int &id) {
    return repository.findById(id);
}

ParcelPtr ParcelManager::registerStandard(int id, double mass, bool isSent, int basePrice) {
    ParcelPtr c = getParcelById(id);
    if(c == nullptr)
    {
        c = std::make_shared<Standard>(id,mass,isSent,basePrice);
        repository.addObject(c);
    }
    return c;
}

ParcelPtr ParcelManager::registerCarefull(int id, double mass, bool isSent, int basePrice, SegmentType segment) {
    ParcelPtr c = getParcelById(id);
    if(c == nullptr)
    {
        c = std::make_shared<Carefull>(id,mass,isSent,basePrice,segment);
        repository.addObject(c);
    }
    return c;
}
// metoda ungerister sluzy do usuwania rejestru
bool ParcelManager::unregisterParcel(const ParcelPtr &parcel) {
    ParcelPtr c = getParcelById(parcel->getId());
    if(c != nullptr) {
        repository.removeObject(c);
        return true;
    }
    return false;
}


