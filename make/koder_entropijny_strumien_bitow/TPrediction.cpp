#include "TPrediction.h"

TPrediction::TPrediction(int** piImageMatrix, int iWidth, int iHeight, int iBlockSize)
{
  m_piImageMatrix= piImageMatrix;
  m_iWidth= iWidth;
  m_iHeight= iHeight;
  m_iBlockSize= iBlockSize;
  m_iActualWidth=0;
  m_iActualHeight=0;
  m_iMotionVectorX=0;
  m_iMotionVectorY=0;
  m_iMotionValue=0;
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
  m_piMotion = new int* [iRows];
  for (int i = 0; i < iRows; ++i)
  {
    m_piMotion[i] = new int[iCols];
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

   
}

void TPrediction::PredictionMotion()
{
  if (m_iActualHeight == 0 && m_iActualWidth == 0) // pierwszy blok nie da siê zrobiæ predykci - wysy³amy oryginalny blok
  {
    for (int i = 0; i < m_iBlockSize; i++)
    {
      for (int j = 0; j < m_iBlockSize; j++)
      {
        m_piMotion[i][j] = m_piImageMatrix[i][j];
      }
    }
    cerr << "predykcja ruchu blok 0" << endl;
    cerr << "obraz orginalny: " << endl;
    for (int i = 0; i < m_iBlockSize; i++)
    {
      for (int j = 0; j < m_iBlockSize; j++)
      {
        cerr << m_piImageMatrix[i][j] << " ";
      }
      cerr << endl;
    }
    cerr << "obraz zakodowany: " << endl;
    for (int i = 0; i < m_iBlockSize; i++)
    {
      for (int j = 0; j < m_iBlockSize; j++)
      {
        cerr << m_piMotion[i][j] << " ";
      }
      cerr << endl;
    }
  }
  else // mozna liczyc predykcje
  {
    //--------------------------------
//------------------------------------------------
    if (m_iActualWidth > 8) //wiecej niz dwa blok
    {
      if (m_iActualHeight > 8)
      {// dzia³a!
        cerr << "jestem w warunku to i to wieksze ni¿ 8 " << endl;
        int counterX = m_iActualHeight - 7;
        int lines = (22 * 8) - 7;
        for(int l=0;l<m_iActualWidth/8+1;l++)
        { 
          if (l == m_iActualWidth / 8)
          {
            lines = m_iActualWidth - 7;
          }
          for (int i = 0; i < lines; i++)//22 bloki o rozmiarze 8
          {

            for (int k = 0; k < m_iBlockSize; k++)
            {
              for (int j = 0; j < m_iBlockSize; j++)
              {
                m_piMotion[k][j] = m_piImageMatrix[k + m_iActualHeight][j + m_iActualWidth] - m_piImageMatrix[k+(l*8)][j + i];//ta druga siê przesuwa
                //cerr << "wspol 1: " << k + (l * 8) << " wspol 2 : " << j + i << endl;
                
              }
            }
            //cin.get();
          }
        }
      }
      else//bierze pod uwage tylko przesuwanie w poziomie bo wysokosc jest rowna 0
      { 
      cerr << "Wysokosc rowna 0 wiecej niz 2 bloki" << endl;
      int counterX = m_iActualWidth - 7;

      for (int i = 0; i < counterX; i++)
      {

        for (int k = 0; k < m_iBlockSize; k++)
        {
          for (int j = 0; j < m_iBlockSize; j++)
          {
            m_piMotion[k][j] = m_piImageMatrix[k + m_iActualHeight][j + m_iActualWidth] - m_piImageMatrix[k][j + i];//ta druga siê przesuwa
          }
        }
        cerr << "counter: " << counterX << endl;
        for (int i = 0; i < m_iBlockSize; i++)
        {
          for (int j = 0; j < m_iBlockSize; j++)
          {
            cerr << m_piMotion[i][j] << " ";
          }
          cerr << endl;
        }
      }
    }
    }
    else //dwa bloki
    {
      if (m_iActualHeight >= 8)//przejdz caly rzad 
      {
        cerr << "rzad 2 bloki wysokosc wieksza ni¿ 1 lub rowna " << endl;
        int counterX = m_iActualHeight - 7;
        int lines = (22 * 8) - 7;
        for (int l = 0; l < m_iActualWidth / 8 + 1; l++)
        {
          if (l == m_iActualWidth / 8)
          {
            lines = m_iActualWidth - 7;
          }
          for (int i = 0; i < lines; i++)//22 bloki o rozmiarze 8
          {

            for (int k = 0; k < m_iBlockSize; k++)
            {
              for (int j = 0; j < m_iBlockSize; j++)
              {
                m_piMotion[k][j] = m_piImageMatrix[k + m_iActualHeight][j + m_iActualWidth] - m_piImageMatrix[k + (l * 8)][j + i];//ta druga siê przesuwa
                cerr << "wspol 1: " << k + (l * 8) << " wspol 2 : " << j + i << endl;

              }
            }
            //cin.get();
          }
        }
      }
      else
      { 
      cerr << "dwa bloki brak rzedu" << endl;
      for (int k = 0; k < m_iBlockSize; k++)
      {
        for (int j = 0; j < m_iBlockSize; j++)
        {
          m_piMotion[k][j] = m_piImageMatrix[k + m_iActualHeight][j + m_iActualWidth] - m_piImageMatrix[k][j];//ta druga siê przesuwa
        }
      }
      cerr << "obraz zakodowany: " << endl;
      for (int i = 0; i < m_iBlockSize; i++)
      {
        for (int j = 0; j < m_iBlockSize; j++)
        {
          cerr << m_piMotion[i][j] << " ";
        }
        cerr << endl;
      }
    }
    }


    cerr << "Macierz obrazu:" << endl;
    for (int x = 0; x < 3; x++)
    {
      for (int i = 0; i < m_iBlockSize; i++)
      {
        for (int j = 0; j < m_iBlockSize; j++)
        {
          cerr << m_piImageMatrix[i][j + (8 * x)] << " ";
        }
        cerr << endl;
      }
      cerr << endl;
    }

  }
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
