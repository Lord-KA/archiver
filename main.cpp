#include <iostream>
#include <string_view>
#include <vector>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "rle.hpp"


void help()
{
    std::cout << "this is an archiver" << std::endl;
}

enum Algorithm { RLE, HUFFMAN};
enum Mode {ARCHIVE, EXTRACT, LIST, TEST};

int main(int argc, char **argv) //TODO add timestamps saving; decoding health check (hashsum crc16/32); add man; add cmake (make install option); add multyfile archivation. 
{
    Algorithm alg = RLE;
    Mode mode = ARCHIVE;
    std::vector<char*> inpFiles;
    bool customOutpName = false;
    std::string outpFileName = "file";

    for (int i=1; i < argc; ++i)
    {
        std::string elem{argv[i]};
        if (elem[0] == '-') //TODO file delete option; add multiotions (like "-nt")
        {   
            if (elem == "--help" || elem == "-h")
                help();

            else if (elem == "-o"){
                if (i + 1 < argc)
                {
                    outpFileName = argv[i + 1];
                    customOutpName = true;
                    ++i;
                }
                else
                {
                    std::cerr << "ERROR: output file is to be provided after clue -o." << std::endl;
                    return EXIT_FAILURE;
                }
            }
            /*
            */

            else if (elem == "--rle")
                alg = RLE;
            else if (elem == "--huffman")
                alg = HUFFMAN;
            
            else
                for (int j=1; j<elem.size(); ++j)
                {
                    if (elem[j] == 'e')
                        mode = EXTRACT;
                    else if (elem[j] == 'l')
                        mode = LIST;
                    else if (elem[j] == 't')
                        mode = TEST;
                        
                }
            
        }
        else
            inpFiles.push_back(argv[i]); 
    }
    if (!inpFiles.size())
    {
        std::cerr << "ERROR: input file is to be provided." << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << mode << std::endl;
    
    if (!customOutpName)
    {
        // check fileformat and make a name
    }
        
    std::ofstream out(outpFileName, std::ofstream::out);


    
    for (auto elem : inpFiles)
    {
        std::ifstream in(elem, std::ifstream::binary);
        if (!in.is_open())
        {
            std::cerr << "ERROR: unable to open file " << elem << std::endl;
            return EXIT_FAILURE;
        }
        switch (alg){
            case RLE:{
                Rle encoder(in, out);
                break; 
            }

            case HUFFMAN: {
                std::cout << "No Huffman yet :(" << std::endl;
                break;
            }
        }
        in.close();
    }

    return 0;
}
