#ifndef COSTREAM
#define COSTREAM

#include <iostream>
#include <fstream>

// #include "cipher.hpp" //TODO create cipher virtual class and derived classes like aes128


static const int buffer_size = 128;

template<typename T>
class costream: public T
{
    public:
        costream() : T() {occupancy = 0;}
        ~costream() { //TODO think if destructor should derived; should there be a service num of the last occupancy?
            if (occupancy)
                for (int i = 0; i < occupancy; ++i)
                    T::put(buf[i]); // It shouldn't stay unencrypted
        }
        T& put (char* s, std::streamsize n) override;
        T& put (std::streambuf& sb) override; //TODO think if it is needed
        //TODO add write()
    private:
        char buf[buffer_size];
        int occupancy;
};


#endif
