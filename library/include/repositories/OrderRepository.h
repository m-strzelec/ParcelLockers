#ifndef PARCELLOCKERS_ORDERREPOSITORY_H
#define PARCELLOCKERS_ORDERREPOSITORY_H

#include <vector>
#include <string>
#include <stdexcept>
#include "typedefs.h"
#include "model/Order.h"
#include "repositories/Repository.h"

class OrderRepository : public Repository<Order> {
public:
    OrderPtr findByOrderId(int id) const;
};


#endif //PARCELLOCKERS_ORDERREPOSITORY_H
