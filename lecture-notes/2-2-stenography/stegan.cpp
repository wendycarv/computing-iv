#include "stegan.hpp"

void hideHelper(std::Image& image, const std::string& msg) {
    sf::Vector2u
    for(size_t i = 0; i<msg.size();i++) {
    char c = msg[i];
    unsigned int x1 = (2*i) % size.x;
    unsigned int x2 = (2*i + 1) % size.x;
    unsigned int y1 = (2*i) / size.y;
    unsigned int y2 = (2*i + 1) / size.y;
    sf::Color p1 = image.getPixel(x1,y1);
    sf::Color p2 = image.getPixel(x2,y2);

    // hide the character
    p1.r = (p1.a & ~0x1) | ((c >> 0) & 0x1); //reverse of 1 at the end | clear out original, or it with hidden character
    p1.g = (p1.a & ~0x1) | ((c >> 1) & 0x1); // 0 1 0 0 1 1 1 0 (original binary) & 1 1 1 1 1 1 1 0 = 0 1 0 0 1 1 1 0 | 0x1 = 0 1 0 0 1 1 1 1
    p1.b = (p1.a & ~0x1) | ((c >> 2) & 0x1); //reverse of 1 at the end
    p1.a = (p1.a & ~0x1) | ((c >> 3) & 0x1); //reverse of 1 at the end
    p2.r = (p2.a & ~0x1) | ((c >> 4) & 0x1); //reverse of 1 at the end | clear out original, or it with hidden character
    p2.g = (p2.a & ~0x1) | ((c >> 5) & 0x1); //reverse of 1 at the end
    p2.b = (p2.a & ~0x1) | ((c >> 6) & 0x1); //reverse of 1 at the end
    p2.a = (p2.a & ~0x1) | ((c >> 7) & 0x1); //reverse of 1 at the end

    image.setPixel(x1,y1,p1);
    image.setPixel(x2,y2,p2);
    // put the pixels back
  }
}
void hideData(sf::Image& image, const std::string& msg) {
  sf::Vector2u size = image.getSize();
  unsigned int totalPixels = size.x *size.y;
  if(msg.size() > totalPixels/2) {
    throw std::invalid_argument("message is too big for the image");
  }
  for(size_t i = 0; i<msg.size(); i++) {
    char c = msg[i];
    hideHelper(image, i, c);
  }
  hideHelper(image,msg.size(), '\0');

}
std::string revealData(sf::Image& image){
    std::string msf;
    sf::Vector2u size = image.getSize();
    unsigned int numPixels = 
    for (size_t i = 0; i < numPixels / 2; i++) {
        unsigned int x1 = (2*i) % size.x;
        unsigned int x2 = (2*i + 1) % size.x;
        unsigned int y1 = (2*i) / size.y;
        unsigned int y2 = (2*i + 1) / size.y;
        sf::Color p1 = image.getPixel(x1,y1);
        sf::Color p2 = image.getPixel(x2,y2);
        char c = 0;
        c |= (p1.r & 0x1) << 0;
        c |= (p1.g & 0x1) << 1;
        c |= (p1.b & 0x1) << 2;
        c |= (p1.a & 0x1) << 3;
        c |= (p2.r & 0x1) << 4;
        c |= (p2.g & 0x1) << 5;
        c |= (p2.b & 0x1) << 6;
        c |= (p2.a & 0x1) << 7;
    }
    return msg;
}