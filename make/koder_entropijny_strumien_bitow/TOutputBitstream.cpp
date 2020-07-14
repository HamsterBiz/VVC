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
      cerr << int(m_uiHeldBits) << endl;
      m_fifo.push_back(m_uiHeldBits);
      m_uiHeldBits = 0;
    }
  }

}           

void TOutputBitstream::PutN8Bit(uint8_t uiNumOfBits, uint8_t uiBits)
{
  for (int i = 0; i < uiBits; i++)
  {
    iMask_ = 1;
    iMask_ <<= (7 - i); //sprawdzanie czy na pierwszej pozycji uiNumOfBits (bit najbardziej znacz¹cy znajduje siê 1)

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
      cerr << int(m_uiHeldBits) << endl;
      m_fifo.push_back(m_uiHeldBits);
      m_uiHeldBits = 0;
    }
  }
}

vector<int>* TOutputBitstream::SplitIntoBits(vector<uint8_t>* VectorToSplit)
{
  int temp;
  int counter;
  int i = 7;
  int size = VectorToSplit->size();
  while (!(VectorToSplit->empty()))
  {
    temp = VectorToSplit->back();
    //cerr << "wartoœæ " << int(temp) << endl;
    VectorToSplit->pop_back();
     while(i>=0)
    {
      //cerr << temp % 2 << " ";
      m_iFifoCode.push_back(temp % 2);
      temp /= 2;
      i--;
    }
    i = 7;
  }
  int size2 = m_iFifoCode.size();
  cerr << "size 1: " << size << " size2: " << size2 << endl;

  return nullptr;
}

unsigned TOutputBitstream::GetSizeBuffor()
{
  return m_fifo.size();
}

uint8_t TOutputBitstream::GetValueFromVector(int iId)
{
  return m_fifo[iId];
}

void TOutputBitstream::Write()
{
  std::fstream file;
  file.open("test.bin", ios::in | ios::out | ios::binary);

    for (unsigned i = 0; i < m_fifo.size(); i++)
    {
      file.write(reinterpret_cast<char*>(&m_fifo[i]), sizeof(uint8_t));
    }
  
    file.close();
}
