#ifndef PARCELLOCKERS_PARCEL_H
#define PARCELLOCKERS_PARCEL_H

#include <string>
#include "exceptions/ParcelException.h"

class Parcel {
private:
    int id;
    double mass;
    bool inLocker = true;
    int basePrice;

public:
    Parcel(int id, double mass, bool InLocker, int basePrice);

    virtual ~Parcel()=0;

    virtual double getActualSendPrice()=0 ;

    virtual std::string getParcelInfo();

    virtual std::string getInfo();

    int getId() const;

    double getMass() const;

    bool isInLocker() const;

    int getBasePrice() const;

    void setIsInLocker(bool isInLocker);
};


#endif //PARCELLOCKERS_PARCEL_H
