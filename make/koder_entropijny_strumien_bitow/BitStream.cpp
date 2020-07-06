#include "BitStream.h"

BitStream::BitStream()
{
  temp_ = 0;
  index_stream_ = 0;
  index_current_stream_ = 15;
}

void BitStream::PutOne(uint8_t a)
{
  mask_ = 1; 
  mask_ <<= 7; // maska przesuwa 1 na stwoj¹ 8 pozycjê aby sprawdziæ czy w zmiennej a znajduje siê coœ na pierwszej pozycji
  cerr << mask_ << endl;
  if (a & mask_) //tak 
  {
    mask_add_ = 1;
    mask_add_ <<= index_current_stream_;
    temp_ = stream_[index_stream_] | mask_add_;
    stream_[index_stream_] = temp_;
    index_current_stream_--;
  }
  else // nie
  {
    index_current_stream_--;
  }

  if (index_current_stream_ < 0)
  {
    index_current_stream_ = 15;
    index_stream_++;
  }

}

void BitStream::PutN(uint8_t a, int n)
{
  for (int i = 0; i < n; i++)
  {
    mask_ = 1;
    mask_ <<= (7-i);
    if (a & mask_) //tak 
    {

      mask_add_ = 1;
      mask_add_ <<= index_current_stream_;
      temp_ = stream_[index_stream_] | mask_add_;
      stream_[index_stream_] = temp_;
       cerr << (unsigned int)stream_[index_stream_] << endl;
      index_current_stream_--;
    }
    else // nie
    {
      index_current_stream_--;
    }

    if (index_current_stream_ < 0)
    {
      index_current_stream_ = 15;
      index_stream_++;
    }

  }

}

void BitStream::Write(int n)
{
  std::fstream file;
  file.open("test.bin", ios::in | ios::out | ios::binary);

    for (int i = 0; i < n; i++)
    {
      cerr << "zapisuje" << endl;
      file.write(reinterpret_cast<char*>(&stream_[i]), sizeof(stream_[i]));
    }
  
    file.close();
}
