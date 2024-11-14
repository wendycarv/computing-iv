#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

int cachier(std::vector<int> coins, int amt) {
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    int result = 0;
    while (amt > 0) {
        auto mark = std::find_if(coins.begin(), coins.end(), [amt](int coin) {
            return coin <= amt;
        });
        if (mark == coins.end()) throw std::invalid_argument("Solution not possible");
        amt -= *mark;
        result++;
    }
    return result;
} // amt we want to match

int opt(std::vector<int> coins, int amt) {

}
int main() {
    std::shared_ptr<int> p1 = std::make_shared<int>();
    std::shared_ptr<int> p2 = p1;
    std::cout << *p1 << *p2 << std::endl;
    *p1 = 4;
    std::cout << *p1 << *p2 << std::endl;

    int amt;
    std::cin >> amt;
    //std::vector<int> coins = { 1, 5, 10, 25, 100 };
    std::vector<int> coins = { 1, 6, 10 };
    std::cout << cachier(coins, amt) << std::endl;
    std::cout << opt(coins, amt) << std::endl;
}