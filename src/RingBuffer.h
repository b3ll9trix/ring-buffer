//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_RINGBUFFER_H
#define SRC_RINGBUFFER_H
#include <vector>

template<typename T>
class RingBuffer {
    public :
        /// Constructor
        explicit RingBuffer(int size);
        /// Destructor
        ~RingBuffer();
        /// put - puts element into the Buffer
        void put(T new_value);
        /// get - gets the oldest element from the Buffer
        T get();
        /// readAll - Reads all elements of the Buffer at the time
        /// TODO: Make it Const
        std::vector<T> readAll();
        /// top - returns the head index
        int top() const;
        /// [] Operator for Random Access
        T &operator[](int index);
        /// [] Operator for Random Access for cont Object
        T &operator[](int index) const;
    private :
        /// Buffer
        std::vector<T> buffer;
        /// Buffer Size
        int buf_size;
        /// Index of the top of the buffer
        int head;
        /// Index of the bottom of the buffer
        int tail;

};


#endif //SRC_RINGBUFFER_H
