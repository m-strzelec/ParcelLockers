#include <managers/ClientManager.h>
#include <managers/OrderManager.h>
#include <managers/ParcelManager.h>
#include "SavingState.h"
#include "typedefs.h"

int main() {
    ClientManager clientman;
    ParcelManager parcelman;
    OrderManager orderman;

    std::ofstream o("parcelLockersInfo.json");

    AddressPtr testaddress1 = std::make_shared<Address>("City", "Street", 1);
    AddressPtr testaddress2 = std::make_shared<Address>("City2", "Street2", 2);

    ClientPtr client1 =clientman.registerClient("Jan","Tomaszewski","223312",testaddress1);
    o << "Client: "<< SavingState::toJSON(client1);
    ClientPtr client2= std::make_shared<Client>("Borys","Borna","223812",testaddress2);
    o << "\n\nClient: "<< SavingState::toJSON(client2);

    ParcelPtr carefull1 =parcelman.registerCarefull(123,5.35,true,20,Electrical);
    o << "\n\nParcel: "<< SavingState::toJSON(carefull1);
    ParcelPtr standard1 =parcelman.registerStandard(344, 4, true, 25);
    o << "\n\nParcel: "<< SavingState::toJSON(standard1);

    OrderPtr order1=orderman.makeOrder(1, client1, carefull1, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0);
    o << "\n\nOrder" << SavingState::toJSON(order1);
    OrderPtr order2=orderman.makeOrder(2, client2, standard1, testaddress2, pt::not_a_date_time, pt::not_a_date_time, 0);
    o << "\n\nOrder"<< SavingState::toJSON(order2);

    orderman.endOrder(order1);
    orderman.endOrder(order2);
    o.close();
    return 0;
}