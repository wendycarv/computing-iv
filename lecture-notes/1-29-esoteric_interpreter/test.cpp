#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BF Test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestHello) {
    std::string program = "";
    Brainfuck bf(program);
    std::stringstream istream;
    std::stringstream o("Hello, World!";
    std::string exp = "Hello, World!";
    bf.run(istream, ostream);
    BOOST_REQUIRE_EQUAL(ostream.str(), exp);
}