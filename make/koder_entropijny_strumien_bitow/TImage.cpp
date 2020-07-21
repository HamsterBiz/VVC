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

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
       cerr << m_piMatrix[j][i]<<",";
    }
  }

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

  int iNumberOfBlockX = m_iWidth /8;
  int iNumberOfBlockY = m_iHeight /8;
  int i, j, u, v;
  double s;
  for (int y = 0; y < iNumberOfBlockY; y++)
  {

   for (int x = 0; x < iNumberOfBlockX; x++)
    {
      for (i = 0; i < 8; i++)
      {
        for (j = 0; j < 8; j++)
        {
          s = 0;

          for (u = 0; u < 8; u++)
          {
            for (v = 0; v < 8; v++)
            {
              s += m_piMatrix[u+(y*8)][v+(x*8)] * cos((2 * u + 1) * i * M_PI / 16) *
                cos((2 * v + 1) * j * M_PI / 16) *((i == 0) ? 1 / sqrt(2) : 1) *((j == 0) ? 1 / sqrt(2) : 1);
            }
          }
          m_piMatrixDCT[i + (y * 8)][j + (x * 8)] = s / 4;
        }
      }
    }
  }
}

void TImage::IDCT8x8()
{
  
    int iRows = m_iHeight, iCols = m_iWidth;
    int counter = 0;
    m_piMatrixIDCT = new int* [iRows];
    for (int i = 0; i < iRows; ++i)
    {
      m_piMatrixIDCT[i] = new int[iCols];
    }
  
    int i, j, u, v;
  double s;
  int iNumberOfBlockX = m_iWidth / 8;
  int iNumberOfBlockY = m_iHeight / 8;
  for (int y = 0; y < iNumberOfBlockY; y++)
  {

    for (int x = 0; x < iNumberOfBlockX; x++)
    {
      for (i = 0; i < 8; i++)
      {
        for (j = 0; j < 8; j++)
        {
          s = 0;

          for (u = 0; u < 8; u++)
          {
            for (v = 0; v < 8; v++)
            { 
              s += m_piMatrixDCT[u + (y * 8)][v + (x * 8)] * cos((2 * i + 1) * u * M_PI / 16) *
              cos((2 * j + 1) * v * M_PI / 16) *((u == 0) ? 1 / sqrt(2) : 1.) *((v == 0) ? 1 / sqrt(2) : 1.);
            }
            }
          m_piMatrixIDCT[i + (y * 8)][j + (x * 8)] = int(s / 4);
        }
      }
    }
  }


}

void TImage::DCTTEST()
{
  int maks = 0;
  for (int i = 0; i < 216; i++)
  {
    for (int j = 0; j < 176; j++)
    {
      if (maks < abs(m_piMatrix[i][j] - m_piMatrixIDCT[i][j]))
      {
        maks = abs(m_piMatrix[i][j] - m_piMatrixIDCT[i][j]);
      }
    }
  }
  cerr << "maksymalna roznica wyników po DCT wynosi: " << maks << endl;
}

void TImage::ZigZag4x4()
{
  cerr << "zigzag 4x4" << endl;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      cerr<<m_piMatrixDCT[i][j] << " ";
    
    }
    cerr << endl;
  }
  int iNumberOfBlockX = m_iWidth / 4;
  int iNumberOfBlockY = m_iHeight / 4;
  int n = 4;
  int m = 4;
  for (int yy = 0; yy < iNumberOfBlockY; yy++)
  {

    for (int xx = 0; xx < iNumberOfBlockX; xx++)
    {
      for (int i = 0; i < n + m - 1; i++)
      {
        if (i % 2 == 1) {
          int x = (i < n) ? 0 : i - n + 1;
          int y = (i < n) ? i : n - 1;
          while (x < n && y >= 0)
          {
            cerr << m_piMatrixDCT[x+(yy*4)][y+(xx*4)] << " ";
            x++; y--;
          }
        }
        else
        {
          int x = i < n ? i : n - 1;
          int y = i < n ? 0 : i - n + 1;
          while (x >= 0 && y < n)
          {
            cerr << m_piMatrixDCT[x+(yy * 4)][y + (xx *4)] << " ";
            x--; y++;
          }
        }
      }
      cerr << endl;
    }
  
  }
}

