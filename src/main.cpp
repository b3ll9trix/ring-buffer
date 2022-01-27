#include <iostream>
#include <thread>
#include <vector>
#include "RingBuffer.h"
#include "Frame.h"

typedef int frame_rate_t;
typedef std::string process_message_t;

bool g_ready = false;


using namespace std::chrono_literals;
/// produce - produces frame every `frame_rate` seconds and pushes into the buffer infinitely
[[noreturn]] void produce(frame_rate_t frame_rate, RingBuffer<Frame<int>> &buffer){
    int i = 0;
    while(true){
        std::vector<int> imageFrame;
        int len =0;
        //Dummy Array
        while(len < g_frame_len) {
            imageFrame.push_back(i);
            i++;
            len++;
        }
        Frame<int> frame = Frame<int>(imageFrame);
        buffer.buffer_mutex->lock();
        buffer.push_back(frame);
        buffer.buffer_mutex->unlock();
        g_ready = true;
        std::cout << "Pushed " << frame.to_string() << "\n";
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
        process_message_t message = "Average of [" + frame.to_string() + "] at Frame#" + std::to_string(frame.number()) + " is " + frame.process()+ " Timestamp:" + frame.timestamp();
        std::cout<<message;

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

