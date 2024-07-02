#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Address.h"

struct ClientTestSuiteFixture {
    std::string testFN = "FirstName";
    std::string testLN = "LastName";
    std::string testPID = "0123456789";
    AddressPtr testAddress1;

    ClientTestSuiteFixture() {
        testAddress1 = std::make_shared<Address>("City", "Street", 1);

    }

    ~ClientTestSuiteFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(ClientTestSuite, ClientTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTests) {
        auto pidPred = [](const ClientException & exception) -> bool {
            return std::string(exception.what()).find("PID") != std::string::npos;
        };
        auto adrPred = [](const ClientException & exception) -> bool {
            return std::string(exception.what()).find("Address") != std::string::npos;
        };

        Client client("ABC", "DEF", "123", testAddress1);
        BOOST_TEST_REQUIRE(&client != nullptr);
        BOOST_CHECK_EXCEPTION(Client client1("FN", "LN", "", testAddress1), ClientException, pidPred);
        BOOST_CHECK_EXCEPTION(Client client2("FN", "LN", "PID", nullptr), ClientException, adrPred);
    }

    BOOST_AUTO_TEST_CASE(GetterTests) {
        Client client(testFN, testLN, testPID, testAddress1);

        BOOST_TEST(client.getFirstName() == testFN);
        BOOST_TEST(client.getLastName() == testLN);
        BOOST_TEST(client.getPersonalID() == testPID);
        BOOST_TEST(client.getAddress() == testAddress1);

        std::string clientId = client.getPersonalID();
        BOOST_TEST(client.getId() == clientId);

        std::string clientInfo = client.getClientInfo();
        BOOST_TEST(clientInfo.find(testFN) != std::string::npos);
        BOOST_TEST(clientInfo.find(testLN) != std::string::npos);
        BOOST_TEST(clientInfo.find(testPID) != std::string::npos);
        BOOST_TEST(clientInfo.find(testAddress1->getAddressInfo()) != std::string::npos);
        BOOST_TEST(client.getInfo() == clientInfo);
    }

BOOST_AUTO_TEST_SUITE_END()