#include <iostream>
#include "RingBuffer.h"


int main() {
    RingBuffer<int> cf = RingBuffer<int>(4);
    cf.put(9);
    cf.put(10);
    cf.put(11);
    cf.put(12);
    auto f = cf.readAll();
    for (auto e: f) {
        std::cout << e;
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << cf[2] << "test";
    std::cout << "\n";

    std::cout << cf.get();
    std::cout << "\n";

    std::cout << cf.top();

    std::cout << "\n";
    std::cout << cf.get();

    return 0;

}
