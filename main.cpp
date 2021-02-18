#include <iostream>
#include <string_view>
#include <vector>
#include <fstream>


void help()
{
    std::cout << "this is an archiver" << std::endl;
}

enum Algorithm { RLE, HUFFMAN};

int main(int argc, char **argv) //TODO add timestamps saving; decoding health check (hashsum crc16/32); add man; add cmake (make install option); add multyfile archivation. 
{
    Algorithm alg = RLE;
    std::vector<char*> InpFiles;

    for (int i=1; i < argc; ++i)
    {
        std::string elem{argv[i]};
        if (argv[i][0] == '-') //TODO file delete option; add multiotions (like "-nt")
        {   
            if (elem == "--help" || elem == "-h")
                help();

            else if (elem == "-o"){
                if (i + 1 < argc)
                {
                    char *OutpFileName = argv[i + 1];
                    bool CustomOutpName = true;
                    ++i;
                }
                else
                {
                    std::cerr << "ERROR: output file is to be provided after clue -o." << std::endl;
                    return EXIT_FAILURE;
                }
            }
            else if (elem =="--rle")
                alg = RLE;
            
            else if (elem == "--huffman")
                alg = HUFFMAN;
        }
        else
            InpFiles.push_back(argv[i]); 
    }
    if (!InpFiles.size())
    {
        std::cerr << "ERROR: input file is to be provided." << std::endl;
        return EXIT_FAILURE;
    }
    
    for (auto elem : InpFiles)
    {
        std::ifstream in(elem, std::ifstream::binary);
        if (!in.is_open())
        {
            std::cerr << "ERROR: unable to open file " << elem << std::endl;
            return EXIT_FAILURE;
        }
        switch (alg){
            case RLE:{
                char CurVal = in.get();
                char OldVal = CurVal;
                size_t cnt = 0;
                
                while (!in.eof()){
                    // std::cout << CurVal << std::endl; // DEBUG
                    if (CurVal != OldVal){
                        std::cout << cnt << static_cast<char>(OldVal);
                        cnt = 1;
                        OldVal = CurVal;
                    }

                    else ++cnt;

                    CurVal = in.get();
                }
                if (cnt) std::cout << cnt << static_cast<char>(OldVal);
                in.close();
                break; 
            }

            case HUFFMAN: {
                break;
            }
        }
    }

    return 0;
}
