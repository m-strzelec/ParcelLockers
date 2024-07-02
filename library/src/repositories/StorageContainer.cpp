#include "repositories/StorageContainer.h"
#include "model/Standard.h"
#include "model/Carefull.h"
#include "model/Order.h"

StorageContainer::StorageContainer()
{
    AddressPtr testaddress1 = std::make_shared<Address>("City", "Street", 1);
    AddressPtr testaddress2 = std::make_shared<Address>("City2", "Street2", 2);
    ClientPtr testclient1= std::make_shared<Client>("Jan","Tomaszewski","223312",testaddress1);
    ClientPtr testclient2= std::make_shared<Client>("Borys","Borna","223812",testaddress2);
    ParcelPtr testparcel1 = std::make_shared<Standard>(204, 3.5, true, 20);
    ParcelPtr testparcel2 = std::make_shared<Carefull>(123, 5.35, true, 30, Electrical);
    ParcelPtr testparcel3 = std::make_shared<Standard>(344, 4, false, 25);
    ParcelPtr testparcel4 = std::make_shared<Carefull>(1026, 2.12, true, 40, LowTemp);
    OrderPtr testorder1=std::make_shared<Order>(1, testclient1, testparcel1, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0);
    OrderPtr testorder2=std::make_shared<Order>(2, testclient2, testparcel3, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0);

    clientrepo.addObject(testclient1);
    clientrepo.addObject(testclient2);
    parcelrepo.addObject(testparcel1);
    parcelrepo.addObject(testparcel2);
    parcelrepo.addObject(testparcel3);
    parcelrepo.addObject(testparcel4);
    orderrepo.addObject(testorder1);
    orderrepo.addObject(testorder2);
}

ClientRepository &StorageContainer::getClientrepo() {
    return clientrepo;
}

OrderRepository &StorageContainer::getOrderrepo() {
    return orderrepo;
}

ParcelRepository &StorageContainer::getParcelrepo()  {
    return parcelrepo;
};