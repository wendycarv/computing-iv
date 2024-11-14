#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BF Test
#include <boost/test/unit_test.hpp>
// #include
#include "stegan.hpp"

BOOST_AUTO_TEST_CASE(TestHello) {
   sf::Image image;
   if (!image.loadFromFile("test-pipe-orig.png")) {
    throw std::runtime_error("Failed to load the image");
   }
   std::string message = "Hello, world";
   std::string exp = message;
   hideData(image,message);
   std::string result = revealData(image);
   BOOST_REQUIRE_EQUAL(result, exp);
}