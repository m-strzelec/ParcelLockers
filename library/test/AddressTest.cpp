#include <boost/test/unit_test.hpp>
#include "model/Address.h"

struct AddressTestSuiteFixture {
    std::string c = "Lodz";
    std::string s = "Zielona";
    int n = 10;
};

BOOST_FIXTURE_TEST_SUITE(AddressTestSuite, AddressTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTests) {
        Address address("ABC", "DEF", 123);
        BOOST_TEST_REQUIRE(&address != nullptr);
        BOOST_CHECK_THROW(Address address1("", "s", 1), ClientException);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        Address address2(c, s, n);

        BOOST_TEST(address2.getCity() == c);
        BOOST_TEST(address2.getStreet() == s);
        BOOST_TEST(address2.getNumber() == n);

        std::string addressInfo = address2.getAddressInfo();
        BOOST_TEST(addressInfo.find(c) != std::string::npos);
        BOOST_TEST(addressInfo.find(s) != std::string::npos);
        BOOST_TEST(addressInfo.find(std::to_string(n)) != std::string::npos);
    }

BOOST_AUTO_TEST_SUITE_END()