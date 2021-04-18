#include "../include/cistream.hpp"

template<typename T>
T& cistream<T>::get(char* s, std::streamsize n){ // is n needed?
    s = buf[buffer_size - occupancy];
    if (occupancy == 0){
        occupancy = buffer_size;
        T::read(buf, buffer_size); 
        // TODO add cipher here
        if (T::eof())
            throw std::runtime_error("Error reading block");
    };
}

template<typename T>
T& cistream<T>::get(std::streambuf& sb){
    
}

template<typename T>
T& cistream<T>::getline(char* s, std::streamsize n, char delim){
    size_t i = buffer_size - occupancy; //TODO test the idea
    while (buf[i % buffer_size] != delim){
        s[i] = buf[i % buffer_size];
        ++i;
        if (i == buffer_size){
            T::read(buf, buffer_size);
            //TODO add cipher here
            if (T::eof())
                throw std::runtime_error("Error reading block");
        }
    }
    if (i % buffer_size != 0){
        char tmp[buffer_size];
        for (int j=0; j<buffer_size; ++j) //TODO think of a better way of copying char[]
            tmp[i] = buf[i];
        int q = i % buffer_size;
        for (int j = q; j < buffer_size; ++j) // and here too
            buf[j - q] = tmp[j]; 

        occupancy = q;
    }
}
