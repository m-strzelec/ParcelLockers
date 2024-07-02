#ifndef PARCELLOCKERS_STANDARD_H
#define PARCELLOCKERS_STANDARD_H

#include <string>
#include "Parcel.h"

class Standard :public Parcel{
public:
    Standard(int id, double mass, bool isSent, int basePrice);

    ~Standard() override;

    double getActualSendPrice()  override;

    std::string getParcelInfo()  override;
};


#endif //PARCELLOCKERS_STANDARD_H
