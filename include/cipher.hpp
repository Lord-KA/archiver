#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <fstream>


class cipher
{
    private:
        static const size_t block_size;
    public:
        virtual void encrypt(char *s) = 0;
        virtual void decrypt(char *s) = 0;
};

#endif
