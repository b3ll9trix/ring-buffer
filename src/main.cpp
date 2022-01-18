#include <iostream>
#include "RingBuffer.h"
#include "Frame.h"


int main() {

    //1. Initialization of the Buffer
    RingBuffer<int> cf = RingBuffer<int>(4);

    //2. Produce - Non blocking
    Frame<int> frame = Frame<int>(4,5);

    //3. Consumer
    cf.push_back(9);
    cf.push_back(10);
    cf.push_back(11);
    cf.push_back(12);
    auto f = cf.readAll();
    for (auto e: f) {
        std::cout << e;
        std::cout << "\n";
    }
    std::cout << "\n";
    std::cout << cf[2] << "test";
    std::cout << "\n";

    std::cout << cf.pop_front();
    std::cout << "\n";

    std::cout << cf.back();

    std::cout << "\n";
    std::cout << cf.pop_front();

    return 0;

}
