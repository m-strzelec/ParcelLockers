#include "model/Order.h"
#include "model/Parcel.h"
#include "model/Client.h"

Order::Order(int id, ClientPtr client, const ParcelPtr& parcel, AddressPtr address, const pt::ptime &beginTime,
             const pt::ptime &endTime, double sentCost) : id(id), client(client), parcel(parcel), address(address), beginTime(beginTime),
                                                       endTime(pt::not_a_date_time), sentCost(sentCost) {

    if(Order::beginTime==pt::not_a_date_time){
        Order::beginTime=pt::second_clock::local_time();
        parcel->setIsInLocker(true);
    }
    if(Order::sentCost==0)
        Order::sentCost=parcel->getActualSendPrice();
}

Order::~Order() = default;

std::string Order::getOrderInfo() const {
    std::string chain;
    std::stringstream begin,end;
    begin<<beginTime;end<<endTime;
    chain= std::to_string(id)+client->getClientInfo()+parcel->getParcelInfo()+begin.str()+end.str();
    return chain;
}

std::string Order::getInfo() const {
    return getOrderInfo();
}

int Order::getId() const {
    return id;
}

ClientPtr Order::getClient() const {
    return client;
}

ParcelPtr Order::getParcel() const {
    return parcel;
}

AddressPtr Order::getAddress() const {
    return address;
}

const pt::ptime &Order::getBeginTime() const {
    return beginTime;
}

const pt::ptime &Order::getEndTime() const {
    return endTime;
}

double Order::getSentCost() const {
    return sentCost;
}

void Order::endOrder(pt::ptime end) {
    if ( !(this->endTime.is_not_a_date_time()) ) throw OrderException("Order conclusion error: order already concluded.");
    pt::ptime currentTime = pt::second_clock::local_time();
    if(end.is_not_a_date_time()) {
        if (currentTime < beginTime) this->endTime = beginTime;
        else this->endTime = currentTime;
    }
    else if (end < beginTime) {
        this->endTime = beginTime;
    }
    else this->endTime = end;
    parcel->setIsInLocker(false);// paczka nie jest w paczkomacie po zakonczeniu zamowienia
}

int Order::getOrderDays() const {
    return std::ceil(pt::time_period(beginTime, endTime).length().hours() / 24);
}

