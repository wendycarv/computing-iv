#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Uniquify Tests
#include <boost/test/unit_test.hpp>

#include "unique.hpp"

BOOST_AUTO_TEST_CASE(TestEmpty) {
    std::vector<int> v = {};
    uniquify(v);
    BOOST_REQUIRE_EQUAL(v.size(), 0);
    std::vector<int> exp = {};
    //BOOST_REQUIRE_EQUAL_COLLECTION(v.begin(), v.end(), exp.begin(), exp.end());
}

BOOST_AUTO_TEST_CASE(Test2) {
    std::vector<int> v = { 1, 2, 1 };
    uniquify(v);
    BOOST_REQUIRE_EQUAL(std::count(v.begin(), v.end(), 1), 1);
    BOOST_REQUIRE_EQUAL(std::count(v.begin(), v.end(), 2), 1);
}

BOOST_AUTO_TEST_CASE(Test3) {
    std::vector<int> v = { 1, 2, 3, 2, 2, 3 };
    uniquify(v);
    BOOST_REQUIRE_EQUAL(v.size(), 3);
    BOOST_REQUIRE_EQUAL(std::count(v.begin(), v.end(), 1), 1);
    BOOST_REQUIRE_EQUAL(std::count(v.begin(), v.end(), 2), 1);
}
