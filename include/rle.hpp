#ifndef RLE_HPP
#define RLE_HPP
#include <fstream>
#include "encoder.hpp"

//зачем final?
class Rle final: public Encoder
{
    public:
        bool Encode() override;
        bool Decode() override ;
        
        Rle(std::istream &in, std::ostream &out) : Encoder(in, out) {};
}; 

#endif
