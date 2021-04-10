#ifndef  Format_hpp
#define  Format_hpp


#include <string>
#include <istream>
#include <ostream>
#include <list>
#include <stdexcept>

#include <cstdint>
#include <ctime>


using std::string;
using std::runtime_error;


struct extra_record
{
  uint16_t type;
  uint16_t size;
  string   data;
};

class Format
{
  private:
    uint8_t  id1, id2, cm, flg;
    uint64_t mtime;
    uint8_t  xfl, os;
    //
    uint16_t xlen;
    std::list<extra_record> extra;
    //
    string   fname;
    string   fcomm;
    uint32_t crc32;
    
    uint64_t crc64;
    uint64_t isize;
  
  public:
    Format();

    void Timestamp( time_t timestamp );
    time_t Timestamp() const;
    
    void Filename( const string & name );
    const string & Filename() const;
    
    void Comment( const string & comm );
    const string & Comment() const;
    
    void HasHeaderChecksum(bool flag);
    bool HasHeaderChecksum() const;
    uint32_t HeaderChecksum(bool recalculate = false);
    
    void DataChecksum(uint64_t checksum);
    uint64_t DataChecksum() const;
    
    void DataSize(uint64_t size);
    uint64_t DataSize() const;
    
    void ReadHeading( std::istream & in );
    void ReadEnding( std::istream & in );
    
    void WriteHeading( std::ostream & out );
    void WriteEnding( std::ostream & out );

    void PrettyOutput();
};

#endif //Format_h
