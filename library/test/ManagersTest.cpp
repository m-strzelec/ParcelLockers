#include <boost/test/unit_test.hpp>
#include "managers/ClientManager.h"
#include "managers/ParcelManager.h"
#include "managers/OrderManager.h"
#include "model/Standard.h"
#include "model/Carefull.h"
#include "model/Order.h"


struct ManagersTestSuiteFixture {

    ClientManager clientman;
    ParcelManager parcelman;
    OrderManager orderman;

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

    ManagersTestSuiteFixture() {
        clientman.registerClient("Borys","Borna","223812",testaddress2);
        parcelman.registerStandard(204, 3.5, true, 20);
        parcelman.registerCarefull(123, 5.35, true, 30, Electrical);
        orderman.makeOrder(2, testclient2, testparcel3, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0);
    }

    ~ManagersTestSuiteFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(ManagersTestSuite, ManagersTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(GetterTests) {
        BOOST_TEST(clientman.getClientByID(testclient2->getPersonalID()) != nullptr);
        BOOST_TEST(clientman.findAllClients().size() == 1);
        BOOST_TEST(parcelman.getParcelById(testparcel1->getId()) != nullptr);
        BOOST_TEST(parcelman.findAllParcels().size() == 2);
        BOOST_TEST_REQUIRE(orderman.findAllOrders().size() == 1);
        BOOST_TEST(orderman.findAllOrders()[0] != nullptr);
    }

    BOOST_AUTO_TEST_CASE(RegisterClientTest) {
    ClientPtr newClient = clientman.registerClient("Jan","Tomaszewski","223312",testaddress1);
    BOOST_TEST(clientman.findAllClients().size()==2);
    BOOST_TEST(clientman.getClientByID(newClient->getPersonalID()) != nullptr);
    BOOST_TEST(clientman.getClientByID(newClient->getPersonalID()) == newClient);
    BOOST_TEST(clientman.registerClient("", "", testclient1->getPersonalID(), testclient1->getAddress()) == newClient);
    BOOST_TEST(clientman.getClientByID(newClient->getPersonalID()) == newClient);

    BOOST_TEST(clientman.unregisterClient(newClient));
    BOOST_TEST(clientman.findAllClients().size() == 1);
    }

    BOOST_AUTO_TEST_CASE(RegisterParcelTest) {
    ParcelPtr newCarefull = parcelman.registerCarefull(1026, 2.12, true, 40, LowTemp);
    ParcelPtr newStandard = parcelman.registerStandard(344, 4, false, 25);
    BOOST_TEST(parcelman.findAllParcels().size()==4);
    BOOST_TEST(parcelman.getParcelById(newCarefull->getId()) != nullptr);
    BOOST_TEST(parcelman.getParcelById(newCarefull->getId()) == newCarefull);
    BOOST_TEST(parcelman.getParcelById(newStandard->getId()) != nullptr);
    BOOST_TEST(parcelman.getParcelById(newStandard->getId()) == newStandard);

    BOOST_TEST(parcelman.unregisterParcel(newCarefull));
    BOOST_TEST(parcelman.unregisterParcel(newStandard));
    BOOST_TEST(parcelman.findAllParcels().size() == 2);
    }
    BOOST_AUTO_TEST_CASE(MakeOrderTest) {
    OrderPtr newOrder = orderman.makeOrder(1, testclient1, testparcel1, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0);
    //BOOST_TEST(orderman.makeOrder(10, testclient2, testparcel2, testaddress2, pt::not_a_date_time, pt::not_a_date_time, 0) != nullptr);
    BOOST_TEST(orderman.findAllOrders().size()==2);
    BOOST_TEST(orderman.getOrderById(newOrder->getId()) != nullptr);
    BOOST_TEST(orderman.getOrderById(newOrder->getId()) == newOrder);
    BOOST_TEST(orderman.findAllOrders()[1]->getClient() == testclient1);

    orderman.endOrder(newOrder);
    BOOST_TEST(orderman.findAllOrders().size()==1);

    OrderPtr newOrder2 = orderman.makeOrder(16, testclient1, testparcel2, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0);

    auto OrdPred = [](const OrderException & exception) {
        return std::string(exception.what()).find("order") != std::string::npos;
        };

    BOOST_CHECK_EXCEPTION(orderman.makeOrder(16, testclient1, testparcel2, testaddress1, pt::not_a_date_time, pt::not_a_date_time, 0), OrderException, OrdPred);
    }


BOOST_AUTO_TEST_SUITE_END()

