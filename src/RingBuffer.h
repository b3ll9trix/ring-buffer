//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_RINGBUFFER_H
#define SRC_RINGBUFFER_H
#include <vector>
#include <armadillo>
#include "Exceptions.h"

template <typename T>
class RingBuffer;

template<template<typename> class T, class X>
class RingBuffer<T<X>> {

    typedef T<X>         value_t;
    typedef T<X>         *value_ptr;
    typedef const T<X>   *const_value_ptr;
    typedef T<X>         &reference;
    typedef const T<X>   &const_reference;
    typedef int index_type, size_type;



    public :
        /// buffer_mutex
        std::mutex *buffer_mutex;

        /// Constructor
        explicit RingBuffer(size_type size)
            : buf_size_(size), back_(0), front_(0), contents_size_(0){
                buffer_.resize(size);
                buffer_mutex = new std::mutex();
        }

        /// Destructor
        ~RingBuffer()= default;

        /// back - returns the most recently pushed
        const_reference back() const{
            index_type back_cpy = back_;
            if(back_cpy - 1 < 0) {
                back_cpy = buf_size_-1;
            }
            return buffer_[back_cpy];
        }
        /// front - returns the least recently pushed
        const_reference front() const{
            return buffer_[front_];
        }
        /// [] Operator for Random Access
        reference operator[](index_type index){
            return buffer_[index];
        }
        /// [] Operator for Random Access for cont Object
        const_reference operator[](index_type index) const{
            return buffer_[index];
        }
        /// size - returns the size of the buffer
        size_type size(){
            return buf_size_;
        }
        /// clear - resets the buffer
        void clear(){
            back_ = front_ = contents_size_ = 0;
        }
        /// empty - checks if all the data so far is already consumed
        bool empty() const{
            return contents_size_ == 0;
        }

        /// push_back - puts element into the Buffer
        void push_back(T<X> new_value){
            buffer_[back_] = new_value;
            increment_back();
            if(++contents_size_ > buf_size_){
                increment_front();
                contents_size_ = buf_size_;
            }
        }
        /// pop_front - gets the least recently pushed element from the Buffer
        value_t pop_front() noexcept(false){
            if (empty()) {
                throw BufferEmptyException();
            }
            value_t currData = buffer_[front_];
            increment_front();
            --contents_size_;
            return currData;
        }
        /// copy - copies all elements of the Buffer at the time
        std::vector<value_t> copy(){
            std::vector<T<X>> result;
            result.reserve(buf_size_);
            for (int i=0; i < buf_size_; i++) {
                result.push_back(pop_front());
            }
            return result;
        }

    private :
        /// Buffer
        std::vector<value_t> buffer_;
        /// Buffer Size
        size_type buf_size_;
        /// Space in buffer to be filled next
        index_type back_;
        /// Space in buffer to be popped next
        index_type front_;
        /// No of elements in the buffer
        int contents_size_;

        ///Helper Functions
        /// Increment Back
        void increment_back(){
            if(++back_ == buf_size_) {
                back_ =0;
            }
        }
        /// Increment Front
        void increment_front(){
            if(++front_ == buf_size_) {
                front_ =0;
            }
        }

};
#endif //SRC_RINGBUFFER_H
