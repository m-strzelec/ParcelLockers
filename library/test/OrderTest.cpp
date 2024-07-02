#include <boost/test/unit_test.hpp>
#include "model/Address.h"
#include "model/Client.h"
#include "model/Order.h"
#include "model/Parcel.h"
#include "model/Standard.h"
#include "model/Carefull.h"
#include "typedefs.h"

struct OrderTestSuiteFixture {
    AddressPtr testAddress1;
    ClientPtr testClient1;
    ParcelPtr testParcel1;
    ParcelPtr testParcel2;
    ParcelPtr testParcel3;
    ParcelPtr testParcel4;

    int testDuration = 48;
    int cost1=0;
    int cost2=0;
    int cost3=0;
    int cost4=0;
    pt::ptime now = pt::second_clock::local_time();
    pt::ptime hNegative = now - pt::hours(testDuration);
    pt::ptime hPositive = now + pt::hours(testDuration);
    pt::ptime minPositive = now + pt::minutes(testDuration);

    OrderTestSuiteFixture() {
        testAddress1 = std::make_shared<Address>("City", "Street", 4);
        testClient1 = std::make_shared<Client>("FN", "LN", "0123456789", testAddress1);
        testParcel1 = std::make_shared<Standard>(204, 3.5, true, 20);
        testParcel2 = std::make_shared<Carefull>(123, 5.35, true, 30, Electrical);
        testParcel3 = std::make_shared<Standard>(344, 4, true, 25);
        testParcel4 = std::make_shared<Carefull>(1026, 2.12, true, 40, LowTemp);
    }

    ~OrderTestSuiteFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(OrderTestSuite, OrderTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTests) {
        Order order(1, testClient1, testParcel1, testAddress1, pt::not_a_date_time, pt::not_a_date_time, cost1);
        BOOST_TEST_REQUIRE(&order != nullptr);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        pt::ptime now = pt::second_clock::local_time();
        std::stringstream nowSS;
        nowSS << now;
        Order order(10, testClient1, testParcel1, testAddress1, now, pt::not_a_date_time, cost1);
        BOOST_TEST(order.getClient() == testClient1);
        BOOST_TEST(order.getParcel() == testParcel1);
        BOOST_TEST(order.getAddress() == testAddress1);
        BOOST_TEST(order.getParcel()->isInLocker() == true);
        BOOST_TEST(order.getSentCost() == testParcel1->getActualSendPrice());
        BOOST_TEST(order.getBeginTime() == now);

        std::string orderInfo = order.getOrderInfo();
        BOOST_TEST(orderInfo.find(testClient1->getClientInfo()) != std::string::npos);
        BOOST_TEST(orderInfo.find(testParcel1->getParcelInfo()) != std::string::npos);
        BOOST_TEST(orderInfo.find(nowSS.str()) != std::string::npos);
        BOOST_TEST(order.getInfo() == orderInfo);

        pt::ptime end = now - pt::hours(24);
    }

    BOOST_AUTO_TEST_CASE(ParameterConstructorTests) {
        Order order(100, testClient1, testParcel1, testAddress1, pt::not_a_date_time, pt::not_a_date_time, cost1);

        BOOST_TEST_REQUIRE( !(order.getBeginTime().is_not_a_date_time()) );
        pt::time_period delta = pt::time_period(order.getBeginTime(), pt::second_clock::local_time());
        BOOST_TEST(delta.length().hours() == 0);
        BOOST_TEST(delta.length().minutes() == 0);
        BOOST_TEST(order.getEndTime().is_not_a_date_time());
        BOOST_TEST(order.getOrderInfo().find("not-a-date-time") != std::string::npos);
    }

    BOOST_AUTO_TEST_CASE(GetOrderDaysTests) {
        Order order1(124, testClient1, testParcel1, testAddress1, now, pt::not_a_date_time, cost1);
        Order order2(33, testClient1, testParcel1, testAddress1, now, pt::not_a_date_time, cost2);
        Order order3(99, testClient1, testParcel1, testAddress1, now, pt::not_a_date_time, cost3);
        order1.endOrder(hPositive);
        order2.endOrder(minPositive);
        order3.endOrder(now);

        BOOST_TEST(order1.getOrderDays() == 2);
        BOOST_TEST(order2.getOrderDays() == 0);
        BOOST_TEST(order3.getOrderDays() == 0);
    }

    BOOST_AUTO_TEST_CASE(EndOrderTimeLogicTests) {
        Order nlt(1, testClient1, testParcel1, testAddress1, hNegative, pt::not_a_date_time, cost1);               //Nadt -> Local Time
        Order nbt(2, testClient1, testParcel2, testAddress1, hPositive, pt::not_a_date_time, cost2);               //Nadt -> Begin Time
        Order bt(3, testClient1, testParcel3, testAddress1, now, pt::not_a_date_time, cost3);                     //Begin Time
        Order vt(4, testClient1, testParcel4, testAddress1, now, pt::not_a_date_time, cost4);                     //Value Time (passed time)

        nlt.endOrder(pt::not_a_date_time);
        nbt.endOrder(pt::not_a_date_time);
        bt.endOrder(hNegative);
        vt.endOrder(hPositive);

        pt::time_period nltp = pt::time_period(nlt.getBeginTime(), nlt.getEndTime());
        pt::time_period nbtp = pt::time_period(nbt.getBeginTime(), nbt.getEndTime());
        pt::time_period btp = pt::time_period(bt.getBeginTime(), bt.getEndTime());
        pt::time_period vtp = pt::time_period(vt.getBeginTime(), vt.getEndTime());

        BOOST_TEST(nltp.length().hours() == testDuration);
        BOOST_TEST(nbtp.length().hours() == 0);
        BOOST_TEST(btp.length().hours() == 0);
        BOOST_TEST(vtp.length().hours() == testDuration);
        BOOST_TEST(pt::time_period(now, hPositive).length().hours() == testDuration);

        BOOST_TEST(nlt.getOrderDays() == 2);
        BOOST_TEST(nbt.getOrderDays() == 0);
        BOOST_TEST(bt.getOrderDays() == 0);
        BOOST_TEST(vt.getOrderDays() == 2);

        BOOST_CHECK_THROW(vt.endOrder(hNegative), OrderException);
        vtp = pt::time_period(vt.getBeginTime(), vt.getEndTime());          //update period
        BOOST_TEST(vtp.length().hours() == testDuration);
        BOOST_TEST(vt.getOrderDays() == 2);
    }
BOOST_AUTO_TEST_SUITE_END()

