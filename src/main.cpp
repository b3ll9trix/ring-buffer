#include <iostream>
#include "RingBuffer.h"
#include "Frame.h"
#include <thread>

typedef int frame_rate_t;
typedef std::string process_message_t;

bool g_ready = false;

using namespace std::chrono_literals;
/// produce - produces frame every `frame_rate` seconds and pushes into the buffer infinitely
[[noreturn]] void produce(frame_rate_t frame_rate, RingBuffer<Frame<int>> &buffer){
    int i = 0;
    while(true){
        Frame<int> frame = Frame<int>(i);
        buffer.buffer_mutex->lock();
        buffer.push_back(frame);
        buffer.buffer_mutex->unlock();
        g_ready = true;
        std::cout << "Pushed " << frame.data() << "\n";
        std::this_thread::sleep_for(frame_rate*1s);
        i += 7;
    }
}

/// consume - consumes the oldest frame and processes it
[[noreturn]] void consume(RingBuffer<Frame<int>> &buffer){
    while(true){
        while(!g_ready){

        }
        Frame<int> frame;
        try {
            std::unique_lock<std::mutex> ul(*buffer.buffer_mutex);
            frame = buffer.pop_front();
        }
        catch(BufferEmptyException &exception){
            std::cout<< exception.what();
            g_ready = false;
            continue;
        }
        //Dummy processing to see if the number is even or odd
        if (frame.data() % 2 ==0){
            process_message_t message = "Data " + std::to_string(frame.data())+ " at Frame#" + std::to_string(frame.number()) + " is Even. " + "Timestamp:" + frame.timestamp();
            std::cout<<message;
        }
        else {
            process_message_t message = "Data " + std::to_string(frame.data())+ " at Frame#" + std::to_string(frame.number()) + " is Odd. " + "Timestamp:" + frame.timestamp();
            std::cout << message;
        }
    }
}


int main() {

    //1. Initialization of the Buffer
    //TODO: Template Overloading
    int buffer_size, frame_rate;
    std::cout << "Buffer Size:";
    std::cin >> buffer_size;
    std::cout << "Frame Rate in seconds:";
    std::cin >>frame_rate;
    RingBuffer<Frame<int>> cb = RingBuffer<Frame<int>>(buffer_size);


    //2. Produce - Non blocking
    std::thread thread1(produce,frame_rate, std::ref(cb));

    //3. Consumer - Non blocking
    std::thread thread2(consume, std::ref(cb));

    //4. Wait
    thread1.join();
    thread2.join();


    return 0;

}

