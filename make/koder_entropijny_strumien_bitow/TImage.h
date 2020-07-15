#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include <iostream>
#include <vector>
#pragma warning(disable : 4996)

class TImage
{
private:
  int** m_piMatrix;
  int m_iWidth;
  int m_iHeight;
public:
  TImage(int** piMatrix, int iWidth, int iHeight);
  int GetHeight();
  int GetWidth();
  uint8_t GetValueAt(int y, int x);
  void InsertValueAt(int y, int x, uint8_t value);
};

