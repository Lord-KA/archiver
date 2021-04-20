#ifndef CISTREAM
#define CISTREAM

#include <iostream>
#include <fstream>

// #include "cipher.hpp" //TODO create cipher virtual class and derived classes like aes128


static const size_t buffer_size = 128;

template<typename T>
class cistream: public T
{
    public:
        cistream() : T() {
            occupancy = buffer_size;
            T::read(buf, buffer_size);
            if (T::eof())
                throw std::runtime_error("Error reading block");
        };
        T& get (char* s, std::streamsize n) override;
        T& get (std::streambuf& sb) override; //TODO think if it is needed
        T& getline (char* s, std::streamsize n, char delim = '\n') override;
    private:
        char buf[buffer_size];
        size_t occupancy;
};


#endif
