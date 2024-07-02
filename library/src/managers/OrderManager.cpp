#include "managers/OrderManager.h"

#include <utility>
#include "model/Order.h"

OrderPtr OrderManager::makeOrder(int id, const ClientPtr &client, const ParcelPtr &parcel, const AddressPtr &address,
                                 const pt::ptime &beginTime, const pt::ptime &endTime, int sentCost) {

    if(client == nullptr || parcel == nullptr || address == nullptr) return nullptr;
    if(getOrderById(id) != nullptr)
        throw OrderException("Order instantiation error: order already created.");

    OrderPtr c = getOrderById(id);
    if(c == nullptr)
    {
        c = std::make_shared<Order>(id,client,parcel,address,beginTime,endTime,sentCost) ;
        currentOrders.addObject(c);
    }
    return c;
}

void OrderManager::endOrder(const OrderPtr& order) {

    OrderPtr c = getOrderById(order->getId());// czy jest zamowienie w biezacych
    if ( c== nullptr) return;
    archiveOrders.addObject(c);
    c->endOrder(pt::second_clock::local_time());
    currentOrders.removeObject(c);
}

std::vector<OrderPtr> OrderManager::findOrder(OrderPredicate predicate) {
    return currentOrders.findBy(std::move(predicate));
}

std::vector<OrderPtr> OrderManager::findAllOrders() {
    return currentOrders.findAll();
}
OrderPtr OrderManager::getOrderById(const int &id) {
    return currentOrders.findById(id);
}
