//
// Created by b3ll9trix on 1/18/22.
//

#ifndef SRC_RINGBUFFER_H
#define SRC_RINGBUFFER_H
#include <vector>
template<typename T>
class RingBuffer {

    typedef T          value_type;
    typedef T         *pointer;
    typedef const T   *const_pointer;
    typedef T         &reference;
    typedef const T   &const_reference;
    typedef int index_type, size_type;

    public :
        /// Constructor
        explicit RingBuffer(size_type size)
            : buf_size(size), head(0), tail(0){
                buffer.resize(size);
        }
        /// Destructor
        ~RingBuffer()= default;
        /// put - puts element into the Buffer
        void put(T new_value){
            buffer[head] = new_value;
            if(++head >= buf_size){
                head = 0;
            }
        }
        /// get - gets the oldest element from the Buffer
        value_type get(){
            if(tail+1 >= buf_size){
                int currIndex = tail;
                tail = 0;
                return buffer[currIndex];
            }
            return buffer[tail++];
        }
        /// readAll - Reads all elements of the Buffer at the time
        /// TODO: Make it Const
        std::vector<value_type> readAll(){
            std::vector<T> result;
            result.reserve(buf_size);
            for (int i=0; i < buf_size; i++) {
                result.push_back(get());
            }
            return result;
        }
        /// top - returns the head index
        const_reference top() const{
            return buffer[head];
        }
        /// [] Operator for Random Access
        reference operator[](index_type index){
            return buffer[index];
        }
        /// [] Operator for Random Access for cont Object
        const_reference operator[](index_type index) const{
            return buffer[index];
        }
    private :
        /// Buffer
        std::vector<value_type> buffer;
        /// Buffer Size
        size_type buf_size;
        /// Index of the top of the buffer
        index_type head;
        /// Index of the bottom of the buffer
        index_type tail;

};
#endif //SRC_RINGBUFFER_H
