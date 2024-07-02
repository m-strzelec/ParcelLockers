#include "repositories/OrderRepository.h"

OrderPtr OrderRepository::findByOrderId(int id) const {
    return findById<int>(id);
}