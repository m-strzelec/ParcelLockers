#ifndef PARCELLOCKERS_CAREFULL_H
#define PARCELLOCKERS_CAREFULL_H
#include <string>
#include "Parcel.h"
enum SegmentType{
    Glass=20,
    Electrical=12,
    LowTemp=15,
};
class Carefull :public Parcel{
private:
    SegmentType segment;
public:
    Carefull(int id, double mass, bool isSent, int basePrice, SegmentType segment);

    ~Carefull() override;

    double getActualSendPrice()  override;

    std::string getParcelInfo()  override;

    SegmentType getSegment() const;

};


#endif //PARCELLOCKERS_CAREFULL_H
