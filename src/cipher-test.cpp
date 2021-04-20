#include "../include/cipher-test.hpp"

static const size_t move = 13;

void cipherTest::encrypt(char* s){
    for (int i = 0; i < block_size; ++i) //можно выйти за пределы массива...
        s[i] += move;                    //можно получить переполнение...
};
void cipherTest::decrypt(char* s){
    for (int i = 0; i < block_size; ++i)
        s[i] -= move;
}
