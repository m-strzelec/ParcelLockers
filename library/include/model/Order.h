#ifndef PARCELLOCKERS_ORDER_H
#define PARCELLOCKERS_ORDER_H

#include <string>
#include <boost/date_time.hpp>
#include "typedefs.h"
#include "exceptions/OrderException.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class Order {
private:
    int id;
    ClientPtr client;
    ParcelPtr parcel;
    AddressPtr address;
    pt::ptime beginTime;
    pt::ptime endTime;
    double sentCost=0;
public:
    Order(int id, ClientPtr client, const ParcelPtr& parcel, AddressPtr address,
          const pt::ptime &beginTime, const pt::ptime &endTime, double sentCost);

    ~Order();

    void endOrder(pt::ptime end);

    std::string getOrderInfo() const;

    std::string getInfo() const;

    int getId() const;

    ClientPtr getClient() const;

    ParcelPtr getParcel() const;

    AddressPtr getAddress() const;

    const pt::ptime &getBeginTime() const;

    const pt::ptime &getEndTime() const;

    int getOrderDays() const;

    double getSentCost() const;
};


#endif //PARCELLOCKERS_ORDER_H
