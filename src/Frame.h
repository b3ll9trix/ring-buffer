//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_FRAME_H
#define SRC_FRAME_H
#include<ctime>
template<typename T>
class Frame {

    typedef T data_type;
    typedef int frame_number_type;
    typedef char* timestamp_type;
public:
    /// Constructor
    explicit Frame(data_type data, frame_number_type frame_number)
    :data(data), frame_number(frame_number) {
        std::time_t t = std::time(nullptr);
        timestamp = std::asctime(std::localtime(&t));
    }
    /// Destructor
    ~Frame() = default;

private:
    data_type data;
    frame_number_type frame_number;
    timestamp_type timestamp;


};

#endif //SRC_FRAME_H
