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
      cerr << int(m_uiHeldBits) << endl;
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
  int iSizeQueue = m_fifo.size();
 // cerr << "rozmiar " << iSizeQueue << endl;
  
  while((iSizeQueue - 1)>=0){
  im_uiTemp = m_fifo[iSizeQueue - 1];
  iAmountSaveValue++;
  iSizeQueue--;
  cerr << "wartoœæ : " << int(im_uiTemp) << endl;
  
  counter = 0;
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
     // cerr << int(bits_to_save) << endl;
      iAmuntBit++;
      if (iAmuntBit > 7)
      {
        cerr << "wysyw³a : " << endl;
        m_fifo2.push_back(bits_to_save);
        bits_to_save = 0;
        iAmuntBit = 0;
      }
      x =x/m_ib;
    }
    if (s == 0) x = ((x + 1) * m_iL - 1) / (m_iL - dProbZero_);
    else x = (x * m_iL / dProbZero_);
  }
  }
  //iAmountSaveValue++;
}//dodaæ 

void TOutputBitstream::DecodeSymbols()
{
  int counter3 = 0;
  //int zmienna_od_warunku = iAmuntBit;
  while (iAmountSaveValue) {
    counter3 = 0;
    while (counter3 < 8)
    {
      s = floor(((x + 1) * dProbZero_ - 1) / m_iL) - floor((x * dProbZero_ - 1) / m_iL);
      xq = floor((x * dProbZero_ - 1) / m_iL + 1);
      if (s == 0) x = x - xq;
      else x = xq;

      while (x < m_iL)
      {
        if (iAmuntBit == 0)
        {
          cerr << "tutaj" << endl;
          bits_to_save = m_fifo2.back();
          m_fifo2.pop_back();
          iAmuntBit = 8;
          //counter2 = 0;
        }
        if (counter2 <= iAmuntBit)
        {
          iLoadBit = (bits_to_save & (1 << counter2));
          iLoadBit >>= counter2;
          counter2++;
          //cerr << "counter2: " << counter2 << "iAmountBit" << iAmuntBit << endl;
        }
        else
        {
          //cerr << "warunek " << m_fifo2.empty() << endl;
          if (!m_fifo2.empty())
          {
            //cerr << "tutaj" << endl;
            bits_to_save = m_fifo2.back();
            m_fifo2.pop_back();
            counter2 = 0;
          }

        }
        x = x * m_ib + iLoadBit;

      }

      cerr << " s : " << s << endl;
      counter3++;
    }
    cerr << "-------------" << endl;
    //int iSizeQueue = m_fifo.size();
    
    iAmuntBit = 8;
    //zmienna_od_warunku = 8;
    iAmountSaveValue--;
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
