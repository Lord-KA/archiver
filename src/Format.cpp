#include "../include/Format.hpp"


int EOFflag = 0x00FFFF00;

Format::Format()
: id1(0x1F), id2(0x20), cm(0), flg(0),
  mtime(0), xfl(0), os(0x03), xlen(0),
  fname(), fcomm(), crc32(0),
  crc64(0), isize(0)
{
    fname.reserve(256);
    fcomm.reserve(256);
}


Format::Format(std::string fileName, std::string fileComment) //TODO add os check
: id1(0x1F), id2(0x20), cm(0), flg(0),
  mtime(0), xfl(0), os(0x03), xlen(0),
  fname(), fcomm(), crc32(0),
  crc64(0), isize(0)
{
    fname.reserve(256);
    fcomm.reserve(256);
    flg |= 0x08; // fname
    fname = fileName; //зачем тогда reserve?
    if (!fileComment.empty()){
        flg |=  0x10;
        fcomm = fileComment;
    }


    struct stat result;
    if (stat(fileName.c_str(), &result) == 0)
    {
        mtime = result.st_mtime;
        // isize = result.st_size;
        std::cout << mtime << " " << isize << '\n'; //DEBUG
    }
    else
        throw std::runtime_error("Eror reading metadata with stat()");
    
}

void Format::Timestamp( time_t timestamp )
{
  mtime = timestamp;
}

time_t Format::Timestamp() const
{
  return static_cast<time_t>(mtime);
}

void Format::Filename( const string & name )
{
  if( name.length() == 0 )
  {
    fname.clear();
    flg &= ~0x08 ;
  }
  else
  {
    fname = name;
    flg |=  0x08 ;
  }
}

const string & Format::Filename() const
{
  return fname;
}
    
void Format::Comment( const string & comm )
{
  if( comm.length() == 0 )
  {
    fcomm.clear();
    flg &= ~0x10 ;
  }
  else
  {
    fcomm = comm;
    flg |=  0x10 ;
  }
}

const string & Format::Comment() const
{
  return fcomm;
}

void Format::HasHeaderChecksum(bool flag)
{
  if( flag ) flg |=  0x02;
  else       flg &= ~0x02;
}

bool Format::HasHeaderChecksum() const
{
  return flg & 0x02 ;
}

uint32_t Format::HeaderChecksum(bool recalculate)
{
  if( recalculate )
  {
    //вычисление контрольной суммы заголовка
  }
  
  return crc32;
}

void Format::DataChecksum(uint64_t checksum)
{
  crc64 = checksum;
}

uint64_t Format::DataChecksum() const
{
  return crc64;
}

void Format::DataSize(uint64_t size)
{
  isize = size;
}

uint64_t Format::DataSize() const
{
  return isize;
}

void Format::ReadHeading( std::istream & in )
{
  id1 = in.get();
  if(in.eof()) throw runtime_error("Error reading ID1"); 
  id2 = in.get();
  if(in.eof()) throw runtime_error("Error reading ID2"); 

  if( (id1 != 0x1F) || (id2 != 0x20) )
    throw runtime_error("Error: not rle format"); 

  cm = in.get();
  if(in.eof()) throw runtime_error("Error reading CM"); 
  
  flg = in.get();
  if(in.eof()) throw runtime_error("Error reading FLG"); 

  if(!in.read(reinterpret_cast<char*>(&mtime),8))
    throw runtime_error("Error reading MTIME"); 
  
  xfl = in.get();
  if(in.eof()) throw runtime_error("Error reading XFL"); 
  
  os = in.get();
  if(in.eof()) throw runtime_error("Error reading OS"); 
  
  //
  
  if( flg & 0x04 ) // extra
  {
    if(!in.read(reinterpret_cast<char*>(&xlen),2))
      throw runtime_error("Error reading XLEN"); 
    else {
      if( !in.seekg(xlen,std::istream::cur) ) 
          throw runtime_error("Error positioning"); 
    }
  }
  if( flg & 0x08 ) // fname
  {
    std::getline(in, fname, '\0');
    if( in.eof() ) 
       throw runtime_error("Error reading FNAME"); 
  }
  if( flg & 0x10 ) // fcomm
  {
    std::getline(in, fcomm, '\0');
    if( in.eof() ) 
       throw runtime_error("Error reading FCOMM"); 
  }
  if( flg & 0x02 ) // crc32
  {
    if(!in.read(reinterpret_cast<char*>(&crc32),4))
      throw runtime_error("Error reading CRC32"); 
  }
}

void Format::ReadEnding( std::istream & in )
{
  if(!in.read(reinterpret_cast<char*>(&crc64),8))
    throw runtime_error("Error reading CRC64"); 
  
  if(!in.read(reinterpret_cast<char*>(&isize),8))
    throw runtime_error("Error reading ISIZE"); 
}
    
void Format::WriteHeading( std::ostream & out )
{
  if( !out.put(id1) ) throw runtime_error("Error writing ID1"); 
  if( !out.put(id2) ) throw runtime_error("Error writing ID2"); 

  if( !out.put(cm) )  throw runtime_error("Error writing CM"); 
  
  if( !out.put(flg) ) throw runtime_error("Error writing FLG"); 

  if( !out.write(reinterpret_cast<char*>(&mtime),8) )
    throw runtime_error("Error writing MTIME"); 
  
  if( !out.put(xfl) ) throw runtime_error("Error writing XFL"); 
  
  if( !out.put(os) )  throw runtime_error("Error reading OS"); 
  
  //
  
  if( flg & 0x04 ) // extra
  {
    if( !out.write(reinterpret_cast<char*>(&xlen),2) )
      throw runtime_error("Error writing XLEN"); 
    else {
      if( !out.seekp(xlen,std::ostream::cur) ) 
          throw runtime_error("Error positioning"); 
    }
  }
  if( flg & 0x08 ) // fname
  {
    if( !out.write(fname.c_str(),fname.length()+1) )
      throw runtime_error("Error writing FNAME"); 
  }
  if( flg & 0x10 ) // fcomm
  {
    if( !out.write(fcomm.c_str(),fcomm.length()+1) )
      throw runtime_error("Error writing FCOMM"); 
  }
  if( flg & 0x02 ) // crc32
  {
    if( !out.write(reinterpret_cast<char*>(&crc32),4) )
      throw runtime_error("Error writing CRC32"); 
  }
}
    
void Format::WriteEnding( std::ostream & out )
{
  if( !out.write(reinterpret_cast<char*>(&EOFflag), 4))
      throw runtime_error("Error writing eof flag");

  if( !out.write(reinterpret_cast<char*>(&crc64),8) )
    throw runtime_error("Error writing CRC64"); 
  
  if( !out.write(reinterpret_cast<char*>(&isize),8) )
    throw runtime_error("Error writing ISIZE"); 
}

void Format::PrettyOutput()
{
    std::cout << "-------- " << Filename(); //TODO add pretty and informative metadata output
}   
