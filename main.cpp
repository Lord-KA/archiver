#include <iostream>
#include <string_view>
#include <vector>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "rle.hpp"
#include "encoder.hpp"
#include "Format.hpp"
#include "huffman.hpp"

enum Algorithm { RLE, HUFFMAN};
enum Mode {ARCHIVE, EXTRACT, LIST, TEST};

void help()
{
    std::cout << "this is an archiver" << std::endl;
}

std::ifstream open(std::string fileName){
    
    std::ifstream in(fileName, std::ifstream::binary);
    if (!in.is_open()){
        std::cerr << "ERROR: unable to open file " << fileName << std::endl;
        return EXIT_FAILURE;
    }
    return in;
}

Encoder* AlgChoice(Algorithm alg, std::ifstream &in, std::ofstream &out){
    Encoder* encoder;
    if (alg == RLE)
        encoder = new Rle(in, out);
    else if (alg == HUFFMAN)
        encoder = new Huffman(in, out);
    
    return encoder;
} 


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
            else if (elem == "--extract")
                mode = EXTRACT;
            else if (elem == "--list")
                mode = LIST;
            else if (elem == "--test")
                mode = TEST;
            
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
        

    switch (mode){
        case ARCHIVE:{
            std::ofstream out(outpFileName, std::ofstream::out);
            for (auto elem : inpFiles)
            {
                
                Format format;
                format.Filename(elem);
                format.Comment("add other info"); //TODO add other info  
                format.WriteHeading(out);
                
                std::ifstream in = open(elem);

                (*AlgChoice(alg, in, out)).Encode();
                
                in.close();
                format.WriteEnding(out);
            }
            break;
        }
        case EXTRACT:{
            Format format;
            for (auto elem : inpFiles){
                std::ifstream in = open(elem);
                format.ReadHeading(in);
                outpFileName = format.Filename();
                std::cout << format.Comment() << '\n';
                
                while (!in.eof()){
                    std::ofstream out(outpFileName, std::ofstream::out);
                    
                    Encoder *encoder = AlgChoice(alg, in, out);
                    (*encoder).Decode();
                    (*encoder).WriteMetadata(format);
                    delete encoder; //TODO think about deleting derived class
                    }
            }
            break;
        }
        case TEST:{
            //TODO implement testing alg
            break;
        }
        case LIST:{
            Format format;
            for (auto elem : inpFiles){
                std::ifstream in = open(elem);
                format.ReadHeading(in);
                while (!in.eof()){
                    format.PrettyOutput();
                    //TODO Jump to the next file
                    format.ReadHeading(in);
                }
            }
            break;
        }
    }
    return 0;
}
