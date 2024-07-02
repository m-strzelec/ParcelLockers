#include <boost/test/unit_test.hpp>
#include "model/Parcel.h"
#include "model/Standard.h"
#include "model/Carefull.h"
#include "typedefs.h"

struct ParcelTestSuiteFixture {
    int id = 123;
    int id2 = 456;
    double mass = 30.55;
    double mass2 = 15.76;
    bool isInLocker{};
    bool isInLocker2{};
    int basePrice = 20;
    int basePrice2 = 30;
    SegmentType segment = Glass;

    static double standardprice(double baseprice, double mass) {
        return baseprice * mass;
    }

    static double carefullprice(double baseprice, double mass, SegmentType segment) {
        return standardprice(baseprice, mass) + mass * segment/10;
    }
};

BOOST_FIXTURE_TEST_SUITE(ParcelTestSuite, ParcelTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTests) {
        Standard parcel(id, mass, isInLocker, basePrice);
        BOOST_TEST_REQUIRE(&parcel != nullptr);
        BOOST_CHECK_THROW(Standard parcel2( 0, mass, isInLocker, basePrice), ParcelException);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        Carefull carefull(id, mass, isInLocker, basePrice, segment);
        Standard standard(id2, mass2, isInLocker2, basePrice2);

        BOOST_TEST(carefull.getId() == id);
        BOOST_TEST(carefull.getMass() == mass);
        BOOST_TEST(carefull.isInLocker() == isInLocker);
        BOOST_TEST(carefull.getBasePrice() == basePrice);
        BOOST_TEST(carefull.getSegment() == segment);

        BOOST_TEST(standard.getId() == id2);
        BOOST_TEST(standard.getMass() == mass2);
        BOOST_TEST(standard.isInLocker() == isInLocker2);
        BOOST_TEST(standard.getBasePrice() == basePrice2);

        std::string carefullInfo = carefull.getParcelInfo();
        std::string standardInfo = standard.getParcelInfo();
        BOOST_TEST(carefull.getInfo() == carefullInfo);
        BOOST_TEST(standard.getInfo() == standardInfo);
        BOOST_TEST(carefull.getParcelInfo().size() > 0);
        BOOST_TEST(standard.getParcelInfo().size() > 0);

        carefull.setIsInLocker(false);//test settera
        BOOST_TEST(carefull.isInLocker() == false);
    }

    BOOST_AUTO_TEST_CASE(ParcelPriceTests) {
        ParcelPtr parcel1 = std::make_shared<Carefull>(id, mass, isInLocker, basePrice, segment);
        ParcelPtr parcel2 = std::make_shared<Standard>(id2, mass2, isInLocker2, basePrice2);
        double testprice1 = carefullprice(basePrice, mass, segment);
        double testprice2 = standardprice(basePrice2, mass2);
        BOOST_TEST(parcel1->getActualSendPrice() == testprice1);
        BOOST_TEST(parcel2->getActualSendPrice() == testprice2);
    }

BOOST_AUTO_TEST_SUITE_END()