#include "TOutputBitstream.h"

TOutputBitstream::TOutputBitstream()
{
  m_uiNumOfHeldBits = 7;
  dProbZero_ = 0.3;
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
  int save =0 ;
  int s;
  uint8_t xf;

  uint8_t buffer=0;
  uint8_t space=7;

  std::fstream file;
  file.open("test2.bin", ios::in | ios::out | ios::binary);
  uint8_t mask=1;
  while (!m_fifo.empty())
  {
  xf = m_fifo.back();
  cerr << " " << int(xf) << endl ;
  m_fifo.pop_back();
  for (int i = 0; i <= 7; i++) //petla wczytuj¹ca bit po bicie z bufora
  {
    while (x >= 31) // normalizacja - jeœli x > 0001 1111 to zapisz dane 
    {
      save = x % 2;
      cerr << x % 2;
      buffer |= ((save) << space);
      space--;
      if (space > 7)
      {
        file.write(reinterpret_cast<char*>(&buffer), sizeof(buffer)); //zapis binarnych wartoœci do pliku - sprawdzone wartosci pojawiaj¹ce siê w konsoli faktycznie sa zapisane do pliku 
        space = 7;
        buffer = 0;
      }
      x /= 2;
    }
   
    mask = 1;
    mask <<= 7 - i;
    s = xf & mask ;
    s >>= 7 - i;

    if (s == 0) 
    {
      x = ceil((x + 1) / (1 - dProbZero_)) - 1; 
    }
    else x = floor(x / dProbZero_);
  }
  }
  file.close();
}

void TOutputBitstream::DecodeSymbols()
{
  int x = 0;
  int save = 0;
  int s;
  int xq;
  uint8_t xf;
  uint8_t xp;
  int wynik=0;
  int counter = 0;
  uint8_t buffer = 0;
  bool new_value = true;
  uint8_t mask = 1;
  int size_vector = m_fifo2.size();
  std::ifstream file;
  file.open("test2.bin", ios::in | ios::out | ios::binary);
  while (file.read(reinterpret_cast<char*>(&im_uiHeldBits), sizeof(uint8_t)))
  {
    m_fifo2.push_back(im_uiHeldBits);
  }
  file.close();
  //cerr << "size" << m_fifo2.size() << endl;
  x = m_fifo2.back();//wczytanie poczatkowych 8 bitów 
  m_fifo2.pop_back();
  /*
  if (x <= 31) // poczatkowe wczytanie bitow
  {
    x = x << 4;
    if (new_value == true)
    {//pobierz wartoœc z bufora i wstaw jej po³owe
      buffer = m_fifo2[counter];
      m_fifo2.erase(m_fifo2.begin()+counter);
      counter++;
      xf |= (buffer & 15);
      new_value = false;
    }
    else
    {//wstaw drug¹ czesc i przestaw flagê
      xf |= ((buffer & 240) >> 4);
      new_value = true;
    }
    */
    while (!m_fifo2.empty())
    {
      /*Implementacja z Wikipedii*/
      s = ceil((x + 1) * dProbZero_) - ceil(x * dProbZero_);
      cerr << (int(s));
      if (s == 0)
        x = x - ceil(x * dProbZero_);
      else {
        x = ceil(x * dProbZero_);
      }
      while (x <= 31)
      {
        x = x << 4;
        if (new_value == true)
        {//pobierz wartoœc z bufora i wstaw do x po³owe bitów
          buffer = m_fifo2.back();
          m_fifo2.pop_back();
          counter++;
          x |= (buffer & 15);
          new_value = false;
        }
        else
        {//wstaw drug¹ czêœæ bitów która pozosta³a
          x |= ((buffer & 240) >> 4);
          new_value = true;
        }
      }
    }
  //}
    /*implementacja z prezentacji - nie dzia³aj¹ca
      xp = xf * (dProbZero_ - 1);
      wynik = ((xp & 31) >= dProbZero_ - 1);
      xp >>= 4;
      if (wynik == 1)
      {
        xf = xp;
      }
      else
      {
        xf -= xp;
      }
      cerr << wynik;
      while (xf <= 31)
      {
        xf=xf << 4;
        if (new_value == true)
        {//pobierz wartoœc z bufora i wstaw jej po³owe
          buffer= m_fifo2.back();
          m_fifo2.pop_back();
          xf |= (buffer & 15);
          new_value = false;
        }
        else
        {//wstaw drug¹ czesc i przestaw flagê
          xf |= ((buffer & 240)>>4);
          new_value = true;
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
