#ifndef PARCELLOCKERS_PARCELMANAGER_H
#define PARCELLOCKERS_PARCELMANAGER_H

#include "repositories/ParcelRepository.h"
#include "model/Carefull.h"
#include "model/Standard.h"

class ParcelManager {
private:
    ParcelRepository repository;
public:

    ParcelPtr  registerStandard(int id, double mass, bool isSent, int basePrice);

    ParcelPtr registerCarefull(int id, double mass, bool isSent, int basePrice, SegmentType segment);

    bool unregisterParcel(const ParcelPtr &parcel);

    std::vector<ParcelPtr> findParcel(const ParcelPredicate& predicate);

    std::vector<ParcelPtr> findAllParcels();

    ParcelPtr getParcelById(const int &id);
};


#endif //PARCELLOCKERS_PARCELMANAGER_H
