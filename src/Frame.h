//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_FRAME_H
#define SRC_FRAME_H
#include<ctime>
typedef int frame_number_type;
template<typename T>

class Frame {
    typedef T data_type;
    typedef char* timestamp_type;
public:
    /// Constructor
    explicit Frame(data_type &data)
    :frame_data(data), frame_number(frame_count++) {
        std::time_t t = std::time(nullptr);
        frame_timestamp = std::asctime(std::localtime(&t));

    }
    /// Destructor
    ~Frame() = default;

    /// data
    const data_type &data() const{
        return frame_data;
    }
    /// timestamp
    timestamp_type timestamp() const{
        return frame_timestamp;
    }
    /// number - returns the frame number
    frame_number_type number() const{
        return frame_number;
    }

private:
    static frame_number_type frame_count;
    data_type frame_data;
    frame_number_type frame_number;
    timestamp_type frame_timestamp;


};

template<typename  T>
frame_number_type Frame<T>::frame_count = 0;


#endif //SRC_FRAME_H
