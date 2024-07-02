#define BOOST_AUTO_TEST_MAIN//root of all tests suites and cases
#if defined(__GNUC__) || defined(__GNUG__)
    #define BOOST_TEST_DYN_LINK //use shared boost library
#endif
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

struct MyConfig {

    MyConfig() {
        //      unit_test_log.set_format( output_format.XML ); 
        //      unit_test_log.set_threshold_level( log_level::all );
        //      expected_failures(2);
        //      timeout(1);
        //      tolerance(0.0001);
    }

    ~MyConfig() {
    }
};

BOOST_GLOBAL_FIXTURE(MyConfig);