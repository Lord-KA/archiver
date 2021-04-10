#include "rle.hpp"
#include <iostream>

bool Rle::Encode()
{
    int curVal = inp.get();
    int oldVal = curVal;
    int cnt = 0;

    while (!inp.eof()){
        if (curVal != oldVal || cnt == 255){
            std::cout << cnt << '\n';
            outp.put(cnt);
            outp.put(oldVal);
            cnt = 1;
            oldVal = curVal;
        }
        else ++cnt;

        curVal = inp.get();
    }
    if (cnt) {outp.put(cnt); outp.put(oldVal);}

    return true;
}

bool Rle::Decode()
{
    char cnt = inp.get();
    char val = inp.get();
    while (!inp.eof())
    {
        for(size_t i=0; i<static_cast<int>(cnt); ++i)
            outp.put(val);
        cnt = inp.get();
        val = inp.get();
    }
    return true;
}
