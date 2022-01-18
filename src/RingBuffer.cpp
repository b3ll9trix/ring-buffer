//
// Created by b3ll9trix on 1/18/22.
//

#include "RingBuffer.h"
template<typename T>
RingBuffer<T>::RingBuffer(int size)
        : buf_size(size), head(0), tail(0){
    buffer.resize(size);
}

template<typename T>
RingBuffer<T>::~RingBuffer()= default;

template<typename T>
void RingBuffer<T>::put(T new_value){
    buffer[head] = new_value;
    if(++head >= buf_size){
        head = 0;
    }
}

template<typename T>
T RingBuffer<T>::get(){
    if(tail+1 >= buf_size){
        int currIndex = tail;
        tail = 0;
        return buffer[currIndex];
    }
    return buffer[tail++];
}

template<typename T>
std::vector<T> RingBuffer<T>::readAll(){
    std::vector<T> result;
    result.reserve(buf_size);
for (int i=0; i < buf_size; i++) {
        result.push_back(get());
    }
    return result;
}

template<typename T>
int RingBuffer<T>::top() const {
    return head;
}

template<typename T>
T& RingBuffer<T> :: operator[](int index){
    return buffer[index];
}

template<typename T>
T& RingBuffer<T> :: operator[](int index) const{
    return buffer[index];
}

