#include <boost/test/unit_test.hpp>
#include "repositories/ClientRepository.h"
#include "repositories/OrderRepository.h"
#include "repositories/ParcelRepository.h"
#include "model/Standard.h"
#include "model/Carefull.h"
#include "model/Order.h"


struct RepositoriesTestSuiteFixture {
    ClientRepository clients;
    ParcelRepository parcels;
    OrderRepository orders;
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

    RepositoriesTestSuiteFixture() {
        clients.addObject(testclient1);
        parcels.addObject(testparcel1);
        orders.addObject(testorder1);
          }

    ~RepositoriesTestSuiteFixture() = default;
};


BOOST_FIXTURE_TEST_SUITE(RepositoriesTestSuite, RepositoriesTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(AddTests) {

        parcels.addObject(testparcel4);

        BOOST_TEST(clients.size() == 1);
        BOOST_TEST(parcels.size() == 2);
        BOOST_TEST(orders.size() == 1);

        clients.addObject(nullptr);
        parcels.addObject(nullptr);
        orders.addObject(nullptr);

        BOOST_TEST(clients.size() == 1);
        BOOST_TEST(parcels.size() == 2);
        BOOST_TEST(orders.size() == 1);

        BOOST_TEST(clients.getObject(0) == testclient1);
        BOOST_TEST(parcels.getObject(0) == testparcel1);
        BOOST_TEST(parcels.getObject(1) == testparcel4);
        BOOST_TEST(orders.getObject(0) == testorder1);

    }


    BOOST_AUTO_TEST_CASE(RemoveTests) {

        parcels.addObject(testparcel2);
        orders.addObject(testorder2);

        clients.removeObject(nullptr);
        parcels.removeObject(nullptr);
        orders.removeObject(nullptr);

        BOOST_TEST(clients.size() == 1);
        BOOST_TEST(parcels.size() == 2);
        BOOST_TEST(orders.size() == 2);

        clients.removeObject(testclient1);
        parcels.removeObject(testparcel2);
        orders.removeObject(testorder1);
        parcels.removeObject(testparcel3);// nie ma jej w vectorze nic nie bedzie usuniete

        BOOST_TEST(clients.size() == 0);
        BOOST_TEST(parcels.size() == 1);
        BOOST_TEST(orders.size() == 1);

    }
    BOOST_AUTO_TEST_CASE(FindByIdTests) {

        BOOST_TEST(clients.findById("223312")==testclient1);
        clients.addObject(testclient2);
        BOOST_TEST(clients.findById("223812")==testclient2);
        BOOST_TEST(parcels.findById(204)==testparcel1);
        parcels.addObject(testparcel3);
        BOOST_TEST(parcels.findById(344)==testparcel3);
        BOOST_TEST(orders.findById(1)==testorder1);
        orders.addObject(testorder2);
        BOOST_TEST(orders.findById(2)==testorder2);
    }
    BOOST_AUTO_TEST_CASE(RepositoriesFindAll_FindByTests) {
        OrderPredicate  testId1=[](const OrderPtr& ptr){return ptr->getId()==2;};
        ParcelPredicate WeightBelow4=[](const ParcelPtr& ptr){return ptr->getMass() < 4;};
        ClientPredicate NameJan=[](const ClientPtr& ptr){return ptr->getFirstName()=="Jan";};
        clients.addObject(testclient2);
        parcels.addObject(testparcel2);
        parcels.addObject(testparcel3);
        parcels.addObject(testparcel4);
        orders.addObject(testorder2);
        // find all
        BOOST_TEST(clients.findAll().size()==2);
        BOOST_TEST(orders.findAll().size()==2);
        BOOST_TEST(parcels.findAll().size()==4);
        // find by
        BOOST_TEST(clients.findBy(NameJan).size()==1);
        BOOST_TEST(orders.findBy(testId1).size()==1);
        BOOST_TEST(parcels.findBy(WeightBelow4).size()==2);
    }
    BOOST_AUTO_TEST_CASE(ReportTest) {
        orders.addObject(testorder2);
        parcels.addObject(testparcel3);
        clients.addObject(testclient2);
        BOOST_TEST(clients. report() != "");
        BOOST_TEST(parcels.report() != "");
        BOOST_TEST(orders.report() != "");

        BOOST_TEST(clients.report().find(testclient2->getClientInfo()) != std::string::npos);
        BOOST_TEST(parcels.report().find(testparcel3->getParcelInfo()) != std::string::npos);
        BOOST_TEST(orders.report().find(testorder2->getOrderInfo()) != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()
