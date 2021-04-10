#include <iostream>
#include <sstream>
#include <string>
#include "rle.hpp"

int main(int argc, char **argv)
{
  std::string       string;
  std::stringstream stream;
  
  Rle pack(stream,std::cout);
  //--
  while(1)
  {
    std::getline(std::cin,string);
    stream.clear();
    stream.str(string);
    //std::cout << string << '\n';
    pack.encode();
  }
  //--
  
  return 0;
}


