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
  m_piMatrixDCT = nullptr;
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

void TImage::DCT8x8()
{
  if (m_piMatrixDCT == nullptr)
  {
    int iRows = m_iHeight, iCols = m_iWidth;
    int counter = 0;
    m_piMatrixDCT = new int * [iRows];
    for (int i = 0; i < iRows; ++i)
    {
      m_piMatrixDCT[i] = new int[iCols];
    }
  }
  int iNumberOfBlockX = m_iWidth / 8;
    int iNumberOfBlockY = m_iHeight / 8;
  int i, j, u, v, x, y;
  double s;
  
 // for (y = 0; y < iNumberOfBlockY; y++)
  //{
  //  for (x = 0; x < iNumberOfBlockX; x++)
   // {
      for (i = 0; i < 8; i++)
      {
        for (j = 0; j < 8; j++)
        {
          s = 0;

          for (u = 0; u < 8; u++)
          {
            for (v = 0; v < 8; v++)
            {
              s += m_piMatrix[u][v] * cos((2 * u + 1) * i * M_PI / 16) *
                cos((2 * v + 1) * j * M_PI / 16) *
                ((i == 0) ? 1 / sqrt(2) : 1) *
                ((j == 0) ? 1 / sqrt(2) : 1);
              // cerr << "indeks: x" << u + (x * 8) << "y: " << v + (y * 8) << endl;
               //cin.get();
               m_piMatrixDCT[i][j] = s / 4;
            }
          }
        }
      }
   // }
 // }
  
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      cerr << m_piMatrixDCT[i][j]<<" ";
    }
    cerr << endl;
  }
}

void TImage::IDCT8x8()
{
  int i, j, u, v;
  double s;

  for (i = 0; i < 8; i++)
  { 
    for (j = 0; j < 8; j++)
    {
      s = 0;

      for (u = 0; u < 8; u++)
        for (v = 0; v < 8; v++)
          s += m_piMatrixDCT[u][v] * cos((2 * i + 1) * u * M_PI / 16) *
          cos((2 * j + 1) * v * M_PI / 16) *
          ((u == 0) ? 1 / sqrt(2) : 1.) *
          ((v == 0) ? 1 / sqrt(2) : 1.);

      cerr << int(s / 4) <<" ";
    }
    cerr << endl;
  }
  cerr << "zdjecie orginalne" << endl;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      cerr << m_piMatrix[i][j] << " ";
    }
    cerr << endl;
  }
}

