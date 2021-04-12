#include "rle.hpp"
#include <iostream>

bool Rle::Encode()
{
    int curVal = inp.get();
    int oldVal = curVal;
    int cnt = 0;

    while (!inp.eof()){
        if (curVal != oldVal || cnt == 255){
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
    union {char bytes[4]; uint32_t val;} pack;
    pack.bytes[2] = inp.get();
    pack.bytes[3] = inp.get();
    while (!inp.eof())
    {
        pack.bytes[1] = pack.bytes[3]; pack.bytes[0] = pack.bytes[2];
        for(size_t i=0; i<static_cast<int>(pack.bytes[2]); ++i)
            outp.put(pack.bytes[3]);
        pack.bytes[2] = inp.get();
        pack.bytes[3] = inp.get();
        if (pack.val == 0x00FFFF00)
            return true;
    }
    return true;
}
