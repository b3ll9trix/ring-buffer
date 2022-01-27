//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_FRAME_H
#define SRC_FRAME_H
#include<ctime>
int g_frame_len = 5;
typedef int frame_number_t;

template <typename T>
class Frame {
    typedef std::vector<T> data_t;
    typedef std::string timestamp_t
    ;
public:
    /// Default Constructor
    Frame(){}

    /// Constructor
    explicit Frame(data_t &data)
    : frame_data_(data), frame_number_(frame_count_++), frame_len_(g_frame_len) {
        std::time_t t = std::time(nullptr);
        frame_timestamp_ = std::asctime(std::localtime(&t));

    }
    /// Destructor
    ~Frame() = default;

    /// data
    const data_t &data() const{
        return frame_data_;
    }
    /// process
    const std::string process() const {
        int sum =0;
        for(int i=0; i < g_frame_len; i++){
            sum = sum + frame_data_[i];
        }
        return std::to_string(sum / g_frame_len);
    };
    /// timestamp
    timestamp_t timestamp() const{
        return frame_timestamp_;
    }
    /// number - returns the frame number
    frame_number_t number() const{
        return frame_number_;
    }
    /// to_string
    std::string to_string(){
        std::string retStr;
        for(int i=0; i < g_frame_len; i++){
            retStr = retStr + " " +std::to_string(frame_data_[i]);
        }
        return retStr;
    }

private:
    static frame_number_t frame_count_;
    data_t frame_data_;
    frame_number_t frame_number_;
    timestamp_t frame_timestamp_;
    int frame_len_;


};

template <typename T>
frame_number_t Frame<T>::frame_count_ = 0;


#endif //SRC_FRAME_H
