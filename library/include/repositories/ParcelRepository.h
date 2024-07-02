#ifndef PARCELLOCKERS_PARCELREPOSITORY_H
#define PARCELLOCKERS_PARCELREPOSITORY_H

#include <vector>
#include <string>
#include <stdexcept>
#include "typedefs.h"
#include "model/Parcel.h"
#include "repositories/Repository.h"

class ParcelRepository : public Repository<Parcel>{
public:
    ParcelPtr findByParcelId(int id) const;
};


#endif //PARCELLOCKERS_PARCELREPOSITORY_H
