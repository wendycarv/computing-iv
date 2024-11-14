#define BOOST_TEST_DYN_LIN
#define BOOST_TEST_MODULE Complex TEST
#include <boost/test/unit_test.hpp>
#include "Complex.hpp"


BOOST_AUTO_TEST_CASE(TestAdd) {
    Complex z1(1, 5);
    Complex z2(2, 3);
    BOOST_REQUIRE_EQUAL(z1 + z2, Complex(2+ sqrt(2), 3 + sqrt(2)));
    BOOST_REQUIRE_EQUAL(z2 + z1, Complex(2+ sqrt(2), 3 + sqrt(2)));

}

BOOST_AUTO_TEST_CASE(TestSub) {
    Complex z1(1, 5);
    Complex z2(2, 3);
    BOOST_REQUIRE_EQUAL(z1 - z2, Complex(-1, 2));
    BOOST_REQUIRE_EQUAL(z2 - z1, Complex(1, -2));

}

BOOST_AUTO_TEST_CASE(TestMult) {
    Complex z1(1, 5);
    Complex z2(2, 3);
    BOOST_REQUIRE_EQUAL(z1 * z2, Complex(2 - 15, 3 + 10));
    BOOST_REQUIRE_EQUAL(z2 * z1, Complex(2 - 15, 3 + 10));

}