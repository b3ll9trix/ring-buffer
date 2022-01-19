//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_FRAME_H
#define SRC_FRAME_H
#include<ctime>
typedef int frame_number_t;

template<typename T>
class Frame {
    typedef T data_t;
    typedef std::string timestamp_t
    ;
public:
    /// Default Constructor
    Frame(){}

    /// Constructor
    explicit Frame(data_t &data)
    : frame_data_(data), frame_number_(frame_count_++) {
        std::time_t t = std::time(nullptr);
        frame_timestamp_ = std::asctime(std::localtime(&t));

    }
    /// Destructor
    ~Frame() = default;

    /// data
    const data_t &data() const{
        return frame_data_;
    }
    /// timestamp
    timestamp_t timestamp() const{
        return frame_timestamp_;
    }
    /// number - returns the frame number
    frame_number_t number() const{
        return frame_number_;
    }

private:
    static frame_number_t frame_count_;
    data_t frame_data_;
    frame_number_t frame_number_;
    timestamp_t frame_timestamp_;


};

template<typename  T>
frame_number_t Frame<T>::frame_count_ = 0;


#endif //SRC_FRAME_H
