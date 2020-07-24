#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include <iostream>
#include <vector>
#pragma warning(disable : 4996)
#define M_PI 3.142857 
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <vector>
class TImage
{
private:
  int** m_piMatrix;
  int** m_piMatrixDCT;
  int** m_piMatrixIDCT;
  int m_iWidth;
  int m_iHeight;
  vector<__int16> ZigZagVector;
  __int16 temp;
  vector<int> m_iProbability;
public:
  TImage(int** piMatrix, int iWidth, int iHeight);
  int GetHeight();
  int GetWidth();
  uint8_t GetValueAt(int y, int x);
  void InsertValueAt(int y, int x, uint8_t value);
  void DCT8x8(int** Matrix);
  void IDCT8x8();
  void DCTTEST();
  void ZigZag4x4(int** Matrix);
  __int16 GetValueZigZag();
  unsigned GetSizeZigZag();
  vector <int>* CalculateProbability(int L);
  int** GetImageMatrix();
  int** GetDCTMatrix();

};

