#include "rle.hpp"

Rle::Rle(std::ifstream &inp, std::ofstream &outp) : Encoder(inp, outp){};  

bool Rle::encode()
{
    char curVal = inp.get();
    char oldVal = curVal;
    int cnt = 0;

    while (!inp.eof()){
        if (curVal != oldVal || cnt == 255){
            outp << cnt << static_cast<char>(oldVal);
            cnt = 1;
            oldVal = curVal;
        }

        else ++ cnt;
    }
    if (cnt) outp << cnt << static_cast<char>(oldVal);

    return true;
}

bool Rle::decode()
{
    int cnt = inp.get();
    int val = in.get();
}
