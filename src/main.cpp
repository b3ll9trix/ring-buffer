#include <iostream>
#include "RingBuffer.h"
#include "Frame.h"
#include <thread>

typedef int frame_rate_t;
typedef std::string process_message_t;

/// produce - produces frame every `frame_rate` seconds and pushes into the buffer infinitely
[[noreturn]] void produce(frame_rate_t frame_rate, RingBuffer<Frame<int>> &buffer){
    int i = 0;
    while(true){
        Frame<int> frame = Frame<int>(i);
        buffer.push_back(frame);
        i++;
        std::this_thread::sleep_for(std::chrono::nanoseconds(frame_rate));
    }
}

///// consume - consumes the oldest frame and processes it
//[[noreturn]] void consume(RingBuffer<Frame<int>> &buffer){
//    while(true){
//        Frame<int> frame = buffer.pop_front();
//
//        //Dummy processing to see if the number is even or odd
//        if (frame.data() % 2 ==0){
//            process_message_t message = "Data at Frame:" + std::to_string(frame.number()) + "is Even. Timestamp:" + frame.timestamp();
//            std::cout << message;
//        } else {
//            process_message_t message = "Data at Frame:" + std::to_string(frame.number()) + "is Odd. Timestamp:" + frame.timestamp();
//            std::cout << message;
//        }
//    }
//}


int main() {

    //1. Initialization of the Buffer
    RingBuffer<Frame<int>> cb = RingBuffer<Frame<int>>(4);

    //2. Produce - Non blocking
    std::thread thread1(produce, 7, std::ref(cb));

    //3. Consumer

    return 0;

}

