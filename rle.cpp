#include "rle.hpp"

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
    char val = inp.get();
    int cnt = inp.get();
    while (!inp.eof())
    {
        for(int i=0; i<cnt; ++i)
            outp.put(val);
        val = inp.get(); cnt = inp.get();
    }
    return true;
}
