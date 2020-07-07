#include "TInputBitstream.h"

void TInputBitstream::Read(int n)
{
  std::ifstream file;
  file.open("test.bin", ios::in | ios::out | ios::binary);
  const int size = 20;
  char* buffer = new char[size];

  while(file.read(reinterpret_cast<char*>(&im_uiHeldBits), sizeof(uint8_t)))
  {
    m_fifo.push_back(im_uiHeldBits);
  }
  file.close();
}
