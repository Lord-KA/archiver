#include <iostream>
#include <string_view>
#include <vector>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#include "../include/rle.hpp"
#include "../include/encoder.hpp"
#include "../include/Format.hpp"
#include "../include/huffman.hpp"

enum class Algorithm { RLE, HUFFMAN};
enum class Mode {ARCHIVE, EXTRACT, LIST, TEST};

void help()
{
    std::cout << "this is an archiver" << std::endl;
}

std::ifstream& openInpFile(std::string fileName, std::ifstream &in){
    
    in.open(fileName, std::ifstream::binary);
    if (!in.is_open()){
        std::cerr << "ERROR: unable to open file " << fileName << std::endl;
        throw std::runtime_error("Error opening file");
    }
    return in;
}

Encoder* AlgChoice(Algorithm alg, std::ifstream &in, std::ofstream &out){
    Encoder* encoder;
    if (alg == Algorithm::RLE)
        encoder = new Rle(in, out);
    else if (alg == Algorithm::HUFFMAN)
        encoder = new Huffman(in, out);
    
    return encoder;
} 


int main(int argc, char **argv) //TODO add timestamps saving; decoding health check (hashsum crc16/32); add man; add cmake (make install option); add multyfile archivation. 
{
    Algorithm alg = Algorithm::RLE;
    Mode mode = Mode::ARCHIVE;
    std::vector<char*> inpFiles;
    bool customOutpName = false;
    std::string outpFileName = "file";

    for (int i=1; i < argc; ++i)
    {
        std::string elem{argv[i]};
        if (elem[0] == '-') //TODO file delete option; check for repeating inpFiles
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
                alg = Algorithm::RLE;
            else if (elem == "--huffman")
                alg = Algorithm::HUFFMAN;
            else if (elem == "--extract")
                mode = Mode::EXTRACT;
            else if (elem == "--list")
                mode = Mode::LIST;
            else if (elem == "--test")
                mode = Mode::TEST;
            
            else
                for (int j=1; j < elem.size(); ++j)
                {
                    if (elem[j] == 'e')
                        mode = Mode::EXTRACT;
                    else if (elem[j] == 'l')
                        mode = Mode::LIST;
                    else if (elem[j] == 't')
                        mode = Mode::TEST;
                    else{
                        std::cerr << "ERROR: unknown clue provided." << std::endl;
                        return EXIT_FAILURE;
                    }
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
    /* // For clue identification debug
    std::cout << "Mode: " << mode << std::endl;
    std::cout << "Alg: " << alg << std::endl;
    for (auto elem : inpFiles)
        std::cout << "Inp file: " << elem << std::endl;
    std::cout << outpFileName << std::endl;

    return 0;
    */

    if (!customOutpName)
    {
        // check fileformat and make up a name
    }
        

    switch (mode){
        case Mode::ARCHIVE:{
            std::ofstream out(outpFileName, std::ofstream::out);
            for (auto elem : inpFiles)
            {
                
                Format format;
                format.Filename(elem);
                format.Comment("add other info"); //TODO add other info  
                format.WriteHeading(out);
                
                std::ifstream in;
                openInpFile(elem, in);
                Encoder *encoder = AlgChoice(alg, in, out);
                encoder->Encode();
                
                delete encoder;
                in.close();
                format.WriteEnding(out);
            }
            out.close();
            break;
        }
        case Mode::EXTRACT:{
            Format format;
            for (auto elem : inpFiles){
                std::ifstream in;
                openInpFile(elem, in);
                format.ReadHeading(in);
                outpFileName = format.Filename();
                while (!in.eof()){
                    std::ofstream out(outpFileName, std::ofstream::out);
                    
                    Encoder *encoder = AlgChoice(alg, in, out);
                    
                    encoder->Decode();
                    encoder->WriteMetadata(format);
                    format.ReadEnding(in);
                    delete encoder;
                    out.close();
                    try{
                        format.ReadHeading(in);
                    }
                    catch(const std::runtime_error &){
                        break;
                    }
                    outpFileName = format.Filename();
                }
            }
            break;
        }
        case Mode::TEST:{
            //TODO implement recalculating hashsum alg
            break;
        }
        case Mode::LIST:{
            Format format;
            for (auto elem : inpFiles){
                std::ifstream in;
                openInpFile(elem, in);
                format.ReadHeading(in);
                while (!in.eof()){
                    //TODO Jump to the next file
                    format.ReadEnding(in);
                    format.PrettyOutput();
                    format.ReadHeading(in);
                }
            }
            break;
        }
    }
    return 0;
}
