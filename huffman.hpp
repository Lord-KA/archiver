#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include <fstream>
#include "encoder.hpp"

class Huffman: public Encoder
{
    public:
        bool encode();
        bool decode();
        
        Huffman(std::istream &in, std::ostream &out) : Encoder(in, out) {};
}; 

#endif
