#include "LoadBitStream.h"

void LoadBitStream::Read(int n)
{
  std::ifstream file;
  uint16_t x;
  file.open("test.bin", ios::in | ios::out | ios::binary);
  const int size = 20;
  char* buffer = new char[size];

  while(file.read(reinterpret_cast<char*>(&x), sizeof(uint16_t)))
  {

    cerr << "wynik: " << x << endl;
  }
  file.close();

  
}
