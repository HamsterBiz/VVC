#include "TFileReader.h"

TFileReader::TFileReader(int iWidth, int iHeight, string sFileName)
{
  m_iWidth = iWidth;
  m_iHeight = iHeight;
  m_sFilename = sFileName;
  m_iCounter = m_iWidth * m_iHeight;
}

TImage* TFileReader::ReadFrame()
{ 
  int iRows = m_iHeight + (m_iHeight / 2), iCols = m_iWidth;
  int counter = 0;
  int** piMatrix = new int* [iRows];
  for (int i = 0; i < iRows; ++i)
  { 
    piMatrix[i] = new int[iCols];
  }
  //vector<uint8_t> m_uiImageValues;
  m_pfFile = fopen(m_sFilename.c_str(), "rb");
  m_ibBuffor.buf_ = (unsigned char*)malloc(m_iWidth * m_iHeight * 1.5 * sizeof(unsigned  char));
  fread(m_ibBuffor.buf_, sizeof(unsigned char), (m_iWidth * m_iHeight) * 1.5, m_pfFile);

    for (uint16_t y = 0; y < iRows; y++)
    { 
      for (uint16_t x = 0; x < m_iWidth; x++)
      {
        piMatrix[y][x] = m_ibBuffor.buf_[counter];
        counter++;
      }
    }
  fclose(m_pfFile);
  free(m_ibBuffor.buf_);
  TImage* pImage = new TImage(piMatrix, m_iWidth, iRows);
  return pImage;
}
