#include "TPrediction.h"

TPrediction::TPrediction(int** piImageMatrix, int iWidth, int iHeight, int iBlockSize)
{
  m_piImageMatrix= piImageMatrix;
  m_iWidth= iWidth;
  m_iHeight= iHeight;
  m_iBlockSize= iBlockSize;
  int iRows = iHeight, iCols = iWidth;
  int counter = 0;
  m_piPredictionMatrix = new int* [iRows];
  for (int i = 0; i < iRows; ++i)
  {
    m_piPredictionMatrix[i] = new int[iCols];
  }
  iRows = iBlockSize, iCols = iBlockSize;
  m_piLeftToRight = new int* [iRows];
  for (int i = 0; i < iRows; ++i)
  {
    m_piLeftToRight[i] = new int[iCols];
  }
  m_piTopToBottom = new int* [iRows];
  for (int i = 0; i < iRows; ++i)
  {
    m_piTopToBottom[i] = new int[iCols];
  }
  m_piLeftCorner = new int* [iRows];
  for (int i = 0; i < iRows; ++i)
  {
    m_piLeftCorner[i] = new int[iCols];
  }
}

void TPrediction::PredictionLeftToRight()
{
  for (int i = 0; i < m_iBlockSize; i++)
  {
    m_piLeftToRight[i][0] = m_piImageMatrix[i][0];
  }
  for(int j=0;j<m_iBlockSize;j++)
    for (int k = 1; k < m_iBlockSize; k++)
    {
      m_piLeftToRight[j][k] = m_piImageMatrix[j][k] - m_piLeftToRight[j][0];
    }
 // m_piImageMatrix
  cerr << "Macie¿ ogrginalna: " << endl;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      cerr << m_piImageMatrix[i][j] << " ";
    }
    cerr << endl;
  }
  cerr << "macie¿ predykcji" << endl;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      cerr << m_piLeftToRight[i][j] << " ";
    }
    cerr << endl;
  }

}
