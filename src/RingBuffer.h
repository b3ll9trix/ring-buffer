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

        /// back - returns the head
        const_reference back() const{
            return buffer[head];
        }
        /// front - return the tail
        const_reference front() const{
            return buffer[tail];
        }
        /// [] Operator for Random Access
        reference operator[](index_type index){
            return buffer[index];
        }
        /// [] Operator for Random Access for cont Object
        const_reference operator[](index_type index) const{
            return buffer[index];
        }
        /// size - returns the size of the buffer
        size_type size(){
            return buf_size;
        }
        /// clear - resets the buffer
        void clear(){
            head = tail = 0;
        }
        /// empty - checks if all the data so far is already consumed
        bool empty() const{
            return head == tail;
        }

        /// push_back - puts element into the Buffer
        void push_back(T new_value){
            buffer[head] = new_value;
            if(++head >= buf_size){
                head = 0;
            }
        }
        /// pop_front - gets the oldest element from the Buffer
        value_type pop_front(){
            /// TODO: Exception Handling for precondition
            //if (empty()){return -1;}
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
                result.push_back(pop_front());
            }
            return result;
        }

    private :
        /// Buffer
        std::vector<value_type> buffer;
        /// Buffer Size
        size_type buf_size;
        /// Index of the back of the buffer
        index_type head;
        /// Index of the bottom of the buffer
        index_type tail;

};
#endif //SRC_RINGBUFFER_H
