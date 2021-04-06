#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <fstream>

class Encoder
{
    public:
        virtual bool encode() = 0;
        virtual bool decode() = 0;

        Encoder(std::istream &inp, std::ostream &outp) : inp(inp), outp(outp) {};

    protected:
        std::istream &inp;
        std::ostream &outp;
};

#endif
