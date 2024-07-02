#ifndef PARCELLOCKERS_ORDERMANAGER_H
#define PARCELLOCKERS_ORDERMANAGER_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include "repositories/OrderRepository.h"

namespace pt= boost::posix_time;
namespace gr= boost::gregorian;

class OrderManager {
private:
    OrderRepository currentOrders;
    OrderRepository archiveOrders;
public:
    OrderPtr makeOrder(int id, const ClientPtr &client, const ParcelPtr &parcel, const AddressPtr &address,
                       const pt::ptime &beginTime, const pt::ptime &endTime, int sentCost);

    void endOrder(const OrderPtr& order);

    std::vector<OrderPtr> findOrder(OrderPredicate predicate);

    std::vector<OrderPtr> findAllOrders();

    OrderPtr getOrderById(const int &id);
};


#endif //PARCELLOCKERS_ORDERMANAGER_H
