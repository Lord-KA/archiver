#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <fstream>
#include "encoder.hpp"

class Huffman final: public Encoder
{
    public:
        bool Encode() override;
        bool Decode() override;
        
        Huffman(std::istream &in, std::ostream &out) : Encoder(in, out) {};
}; 

#endif
