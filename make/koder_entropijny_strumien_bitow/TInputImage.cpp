#include "TInputImage.h"

TInputImage::TInputImage(int iWidth, int iHeight, int iAmountFrame, string sFileName)
{
  m_iWidth = iWidth;
  m_iHeight = iHeight;
  m_iAmountFrame = iAmountFrame;
  m_sFilename = sFileName;
 // m_iLumaAmount= m_iWidth* m_iHeight;
  //m_iChromaAmount=m_iLumaAmount/4;
  //m_bLuma=true;
  //m_bChroma=true;
  m_iCounter = (m_iWidth * m_iHeight * 1.5)-1;
}

int TInputImage::GetCounter()
{
  return m_iWidth* m_iHeight*1.5;
}

void TInputImage::ReadVideo()
{
  
  
  m_fFile = fopen(m_sFilename.c_str(), "rb");
  m_ibBuffor.buf_ = (unsigned char*)malloc(m_iWidth * m_iHeight * 1.5 * sizeof(unsigned  char));

  for (int f = 0; f < m_iAmountFrame; f++)
  {
    fread(m_ibBuffor.buf_, sizeof(unsigned char), (m_iWidth * m_iHeight) * 1.5, m_fFile);

    for (int i = m_iCounter; i >= 0; i--) //wczytujemy próbki obrazu od koñca
    {
      m_uiImageValues.push_back(m_ibBuffor.buf_[i]);
    }
  }
  fclose(m_fFile);
  free(m_ibBuffor.buf_);
}

vector<uint8_t>* TInputImage::GetVectorImage()
{
  return &m_uiImageValues;
}
