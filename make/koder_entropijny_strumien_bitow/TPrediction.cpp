#include "TPrediction.h"

TPrediction::TPrediction(int** piImageMatrix, int iWidth, int iHeight, int iBlockSize)
{
  m_piImageMatrix= piImageMatrix;
  m_iWidth= iWidth;
  m_iHeight= iHeight;
  m_iBlockSize= iBlockSize;
  m_iActualWidth=0;
  m_iActualHeight=0;
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
    m_piLeftToRight[i][0] = m_piImageMatrix[i+ m_iActualHeight][0+ m_iActualWidth];
  }
  for(int j=0;j<m_iBlockSize;j++)
    for (int k = 1; k < m_iBlockSize; k++)
    {
      m_piLeftToRight[j][k] = m_piImageMatrix[j+ m_iActualHeight][k + m_iActualWidth] - m_piLeftToRight[j][0];
    }
 // m_piImageMatrix
  /*
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
  */
}

void TPrediction::PredictionTopToBottom()
{
  for (int i = 0; i < m_iBlockSize; i++)
  {
    m_piTopToBottom[0][i] = m_piImageMatrix[0 + m_iActualHeight][i + m_iActualWidth];
  }
  for (int j = 0; j < m_iBlockSize; j++)
    for (int k = 1; k < m_iBlockSize; k++)
    {
      m_piTopToBottom[k][j] = m_piImageMatrix[k + m_iActualHeight][j + m_iActualWidth] - m_piTopToBottom[0][j];
    }
  // m_piImageMatrix
  /*
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
      cerr << m_piTopToBottom[i][j] << " ";
    }
    cerr << endl;
  }
  */
}

void TPrediction::PredicitionLeftCorner()
{
  //dopisaæ kolumne i wiersz jako pierwsze wartoœci
  for (int i = 0; i < m_iBlockSize; i++)
  {
    m_piLeftCorner[0][i] = m_piImageMatrix[0 + m_iActualHeight][i + m_iActualWidth];
      m_piLeftCorner[i][0] = m_piImageMatrix[i + m_iActualHeight][0 + m_iActualWidth];
  }
  
  int x, y;
  int counter = 0;
  for (int i = 1; i < m_iBlockSize ; i++)
  {
    x = 1;
    y = i;
    while (x < m_iBlockSize && y < m_iBlockSize )//górny wiersz
    {
 m_piLeftCorner[x][y] = m_piImageMatrix[x + m_iActualHeight][y + m_iActualWidth] - m_piLeftCorner[0][counter];
      x++; y++;
    }
    //x++;
    counter++;
  }
  counter = 0;
  for (int i = 1; i < m_iBlockSize; i++)
  {
    x = 1;
    y = i;
    while (x < m_iBlockSize && y < m_iBlockSize)//górny wiersz
    {
      m_piLeftCorner[y][x] = m_piImageMatrix[y + m_iActualHeight][x + m_iActualWidth] - m_piLeftCorner[counter][0];
      x++; y++;
    }
    //x++;
    counter++;
  }

   /*
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
      cerr << m_piLeftCorner[i][j] << " ";
    }
    cerr << endl;
  }
  */
}

int** TPrediction::GetLeftToRight()
{
  return m_piLeftToRight;
}

int** TPrediction::GetTopToBottom()
{

  return m_piTopToBottom;
}

int** TPrediction::GetLeftCorner()
{
  return m_piLeftCorner;
}

void TPrediction::IncrementHeight()
{
  m_iActualHeight += 8;
  m_iActualWidth = 0;
}

void TPrediction::IncrementWidth()
{
  m_iActualWidth += 8;
}
