#include "TOutputBitstream.h"

TOutputBitstream::TOutputBitstream()
{
  m_uiNumOfHeldBits = 7;
}

void TOutputBitstream::PutN(uint32_t uiNumOfBits, uint32_t uiBits)
{
  for (int i = 0; i < uiBits; i++)
  {
    iMask_ = 1;
    iMask_ <<= (31 - i); //sprawdzanie czy na pierwszej pozycji uiNumOfBits (bit najbardziej znacz¹cy znajduje siê 1)

    if (uiNumOfBits & iMask_) //tak 
    {
      iMaskAdd_ = 1;
      iMaskAdd_ <<= m_uiNumOfHeldBits;
      m_uiHeldBits |= iMaskAdd_;
      m_uiNumOfHeldBits--;
    }
    else // nie
    {
      m_uiNumOfHeldBits--;
    }
    if (m_uiNumOfHeldBits > 7) //  buffor jest pe³ny wpisz go do vektora
    {
      m_uiNumOfHeldBits = 7;
      m_fifo.push_back(m_uiHeldBits);
      m_uiHeldBits = 0;
    }
  }

}

void TOutputBitstream::Write(int n)
{
  std::fstream file;
  file.open("test.bin", ios::in | ios::out | ios::binary);

    for (int i = 0; i < n; i++)
    {
      file.write(reinterpret_cast<char*>(&m_fifo[i]), sizeof(uint8_t));
    }
  
    file.close();
}
