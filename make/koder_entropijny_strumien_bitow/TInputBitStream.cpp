#include "TInputBitstream.h"

void TInputBitstream::Read()
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

void TInputBitstream::Test(uint8_t uiTestBits,int iCounter)
{
if(uiTestBits==m_fifo[iCounter])
  {
  cerr << "t";
  }
else
{
  cerr << "error" << endl;
  cin.get();
}
}
