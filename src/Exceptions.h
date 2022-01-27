//
// Created by b3ll9trix on 1/19/22.
//

#ifndef SRC_EXCEPTIONS_H
#define SRC_EXCEPTIONS_H

#include <iostream>
#include <exception>

class BufferEmptyException : public std::exception{
public:
    ///Constructor
    explicit BufferEmptyException()
        :message_("waiting:buffer is empty. nothing to process.\n"){
    }
    const char* what() const throw(){
        return message_.c_str();
    }
private:
    std::string message_;
};

#endif //SRC_EXCEPTIONS_H
