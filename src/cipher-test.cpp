#include "../include/cipher-test.hpp"

static const int move = 13;

void cipherTest::encrypt(char* s){
    for (int i = 0; i < block_size; ++i)
        s[i] += move;
};
void cipherTest::decrypt(char* s){
    for (int i = 0; i < block_size; ++i)
        s[i] -= move;
}
