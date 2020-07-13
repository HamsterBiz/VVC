#include "TOutputBitstream.h"

TOutputBitstream::TOutputBitstream()
{
  m_uiNumOfHeldBits = 7;
  dProbZero_ = 4;
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

  //im_uiTemp = m_fifo[m_fifo.size()-1];
  im_uiTemp = 128;
  cerr << "wartoœæ : " << int(im_uiTemp) << endl;
  while (counter < 8) {

    mask_tem = 1;
    mask_tem <<= counter;
    s = mask_tem & im_uiTemp;
    //cerr << "test bitow" << s << endl;
    counter++;
    m_iUs = 0;
    if (s == 0) m_iUs = m_ib * (m_iL - dProbZero_);
    else m_iUs = m_ib * dProbZero_;
    while (x >= m_iUs)
    {
      cerr << "s " << x % m_ib << endl;
      bits_to_save <<= 1;
      bits_to_save |= (x % m_ib);
      cerr << int(bits_to_save) << endl;
      amuntbit++;
      if (amuntbit > 6)
      {
        cerr << "ERROR" << endl;
      }
      x =x/m_ib;
    }
    if (s == 0) x = ((x + 1) * m_iL - 1) / (m_iL - dProbZero_);
    else x = (x * m_iL / dProbZero_);
  }
  cerr <<"x koniec:"<< int(x) << endl;
  cerr << "bity zapisane " << int(bits_to_save) << endl;
}//dodaæ 

void TOutputBitstream::DecodeSymbols()
{
  cerr << " x " << x << endl;
  cerr << "wynik s: " << floor(((x + 1) * dProbZero_ - 1) / m_iL) - floor((x * dProbZero_ - 1) / m_iL)<<endl;
  s = floor(((x + 1) * dProbZero_ - 1) / m_iL) - floor((x * dProbZero_ - 1) / m_iL);
  xq = floor((x * dProbZero_ - 1) / m_iL + 1);
  if (s == 0) x = x - xq;
  else x = xq;

  while (x < m_iL)
  {
    if (counter2 <= amuntbit)
    {
      tempxxx = (bits_to_save & (1 << counter2));
      tempxxx >>= counter2;
      counter2++;
    }
    x = x * m_ib + tempxxx;
   //i--;
  }

  cerr << " s : "<<s << endl;
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
