#include "TImage.h"

TImage::TImage(int** piMatrix, int iWidth,int iHeight)
{
  if (piMatrix == nullptr)
  {
    int iRows = iHeight, iCols = iWidth;
    int counter = 0;
    m_piMatrix = new int* [iRows];
    for (int i = 0; i < iRows; ++i)
    {
      m_piMatrix[i] = new int[iCols];
    }
  }
  else m_piMatrix = piMatrix;
  m_iWidth= iWidth;
  m_iHeight= iHeight;
}

int TImage::GetHeight()
{
  return m_iHeight;
}

int TImage::GetWidth()
{
  return m_iWidth;
}

uint8_t TImage::GetValueAt(int y, int x)
{
  return m_piMatrix[y][x];
}

void TImage::InsertValueAt(int y, int x, uint8_t value)
{
  m_piMatrix[y][x] = value;
}

