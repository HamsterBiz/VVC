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
  int x=0;
  int s;
  uint8_t xf;
  double xn;
  uint8_t buffer;
  bool BbufferIsEmpty=true;

  uint8_t mask=1;
 // cerr << int(xf) << endl;
  while (!m_fifo.empty())
  {
  xf = m_fifo.back();
  cerr << " kolejnySymbol " << int(xf) << " " << endl;
  m_fifo.pop_back();
  for (int i = 0; i <= 7; i++)
  {
    cerr<<x % 2;
    x /= 2;
    mask = 1;
    mask <<= 7 - i;
    s = xf & mask ;
    s >>= 7 - i;
   // cerr << (int)s << endl;
    if (s == 0)
    {
      x = ceil((x + 1) / (1 - dProbZero_)) - 1;
    }
    else x = floor(x / dProbZero_);
   // s = ceil((x + 1) * dProbZero_) - ceil(x * dProbZero_);
    //cerr <<"s"<< s << endl;

  }
  }
 // 
 // cerr << s << endl;
  /*
  while (!m_fifo.empty())
  {

      xf = x & 15;
      xn = dProbZero_ * (x >> 4);
     // cerr << "x xf xn " << int(x) <<"  "<< int (xf) << "  " << double(xn) << endl;
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
      if (x < 15)
      {
       // cerr <<"mniejsze" 
          
          
        //  << endl;
        x << 4;
        if (BbufferIsEmpty == true)
        {
          buffer = m_fifo.back();
          m_fifo.pop_back();
          BbufferIsEmpty = false;
          x |= (buffer & 240)>>4;
        }
        else 
        {
          x |= buffer & 18;
          BbufferIsEmpty = true;
        }
        
      }
    
  }
  */
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
