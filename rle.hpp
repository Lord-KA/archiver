#ifndef RLE_HPP
#define RLE_HPP
#include <fstream>
#include "encoder.hpp"

class Rle: public Encoder
{
    public:
        bool encode();
        bool decode();

        Rle(std::ifstream &inp, std::ofstream &outp);

    private:
        std::ifstream inp;
        std::ofstream outp;
}; 

#endif
