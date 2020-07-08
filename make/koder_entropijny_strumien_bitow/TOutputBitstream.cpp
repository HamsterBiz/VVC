#include "TOutputBitstream.h"

TOutputBitstream::TOutputBitstream()
{
  m_uiNumOfHeldBits = 7;
  dProbZero_ = 0.75;
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

unsigned TOutputBitstream::GetSizeBuffor()
{
  return m_fifo.size();
}

uint8_t TOutputBitstream::GetValueFromVector(int iId)
{
  return m_fifo[iId];
}

void TOutputBitstream::CodeSymbols()
{
  uint8_t x;
  uint8_t xf;
  uint8_t xn;
  cerr << "halo" << endl;
  while (!m_fifo.empty())
  {
    x = m_fifo.back();
    cerr << " kolejnySymbol " << int(x) << " " << endl;
    m_fifo.pop_back();
    do {
      xf = x & 0x11;

      xn = dProbZero_ * (x >> 4);
      //cerr << "x xf xn" << x << xf << xn << endl;
      //cin.get();
      if (xf < dProbZero_)
      {
        x = xn + xf;
        cerr << "0";
      }
      else
      {
        x -= xn + dProbZero_;
        cerr << "1";
      }
    } while (x >=16);
    cerr << endl;
  }
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
