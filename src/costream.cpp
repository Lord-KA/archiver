#include "../include/costream.hpp"

template<typename T>
T& costream<T>::put (char* s, std::streamsize n){ //is n needed?
    buf[occupancy] = *s;
    ++occupancy;
    if (occupancy == buffer_size){
        //TODO add cipher here
        if (!T::write(buf, buffer_size)) //TODO check format of T::write()
            throw std::runtime_error("Error writing block");

        occupancy = 0;
    }
};

