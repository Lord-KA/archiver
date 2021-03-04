#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <fstream>

class Encoder
{
    public:
        virtual bool encode() = 0;
        virtual bool decode() = 0;

        Encoder(std::ifstream &inp, std::ofstream &outp);
        virtual ~Encoder() = 0;

    private:
        std::ifstream &inp;
        std::ofstream &outp;
};

Encoder::~Encoder(){};

#endif
