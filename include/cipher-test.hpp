#ifndef CIPHER_TEST_HPP
#define CIPHER_TEST_HPP

#include "cipher.hpp"


class cipherTest : public cipher
{
    private:
        static const size_t block_size = 128;
    public:
        void encrypt(char *s) override;
        void decrypt(char *s) override;
};

#endif
