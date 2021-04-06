#ifndef RLE_HPP
#define RLE_HPP
#include <fstream>
#include "encoder.hpp"

class Rle: public Encoder
{
    public:
        bool encode();
        bool decode();
        
        Rle(std::istream &in, std::ostream &out) : Encoder(in, out) {};
}; 

#endif
