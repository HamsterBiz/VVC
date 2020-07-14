#include "TOutputBitstream.h"

TOutputBitstream::TOutputBitstream()
{
  m_uiNumOfHeldBits = 7;
  dProbZero_ =4;//8
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
  
  while((iSizeQueue - 1)>=0){
  im_uiTemp = m_fifo[iSizeQueue - 1];
  m_test1.push_back(im_uiTemp);
  iAmountSaveValue++;
  iSizeQueue--;
 // cerr << "wartoœæ : " << int(im_uiTemp) << endl;
  
  counter = 0;
  while (counter < 8) {

    mask_tem = 1;
    mask_tem <<= counter;
    s = mask_tem & im_uiTemp;
    counter++;
    m_iUs = 0;
    if (s == 0) m_iUs = m_ib * (m_iL - dProbZero_);
    else m_iUs = m_ib * dProbZero_;
    while (x >= m_iUs)
    {
      //cerr << "s " << x % m_ib << endl;
      bits_to_save <<= 1;
      bits_to_save |= (x % m_ib);
      iAmuntBit++;
      if (iAmuntBit > 7)
      {
        m_fifo2.push_back(bits_to_save);
        bits_to_save = 0;
        iAmuntBit = 0;
      }
      x = floor(x/m_ib);
    }
    if (s == 0) x = floor(((x + 1) * m_iL - 1) / (m_iL - dProbZero_));
    else x = floor((x * m_iL / dProbZero_));
  }
  }
}//dodaæ 

void TOutputBitstream::DecodeSymbols()
{
  int counter3 = 0;
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
        if (iAmuntBit == 0 )
        {
          bits_to_save = m_fifo2.back();
          m_fifo2.pop_back();
          iAmuntBit = 8;
        }
        if (counter2 < iAmuntBit)
        {
          iLoadBit = (bits_to_save & (1 << counter2));
          iLoadBit >>= counter2;
          counter2++;
          if (counter2 == iAmuntBit)
          {
            if (!m_fifo2.empty())
            {
              bits_to_save = m_fifo2.back();
              m_fifo2.pop_back();
              counter2 = 0;
              iAmuntBit = 8;
            }
          }

        }
        
        x = x * m_ib + iLoadBit;

      }

     // cerr << " s : " << s << endl;
      iCounterResult++;
      im_uResultSave <<= 1;
      im_uResultSave += s;
      if (iCounterResult > 7)
      {
        m_test2.push_back(im_uResultSave);
        im_uResultSave = 0;
        iCounterResult = 0;

      }
      counter3++;
    }
    
    iAmuntBit = 8;
    iAmountSaveValue--;
  }
}

void TOutputBitstream::CheckTheCodingIsCorrect()
{
  cerr<< m_test1.size();
  cerr<<" "<< m_test2.size();
  int temp_size = m_test1.size()-1 ;
  for (unsigned i = 0; i < temp_size; i++)
  {
    if (i != 0)
    {
      if ((m_test1[i] == m_test2[temp_size - i]))
      {
        cerr << "t";
      }
      else {
        cerr << " i " << i << endl;
        cerr << "rozmiar: " << m_test2.size() << endl;
        cerr << "petla: " << temp_size << endl;
        cerr << "ERROR" << endl;
        cerr << "test1 : " << int(m_test1[i]) << " test2: " << int(m_test2[1]) << " test" << int(m_test2[temp_size - i]) << endl;
        cin.get();
      }
    }
    else
    {
      if ((m_test1[i] == m_test2[temp_size]))
      {
        cerr << "t";
      }
      else {
        cerr << " Error:  " << int(m_test1[i]) << " " << int(m_test2[temp_size])<<endl;
        cerr << " i jest równe 0" << endl;
        cin.get();
      }
    }
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
