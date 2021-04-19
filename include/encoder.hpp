#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <fstream>
//почему не "class Format;"?
#include "Format.hpp"


class Encoder
{
    public:
        virtual bool Encode() = 0;
        virtual bool Decode() = 0;

        Encoder(std::istream &inp, std::ostream &outp) : inp(inp), outp(outp) {};
        virtual ~Encoder() = default;

        void WriteMetadata(Format format);


    protected:
        std::istream &inp;
        std::ostream &outp;
};

#endif
