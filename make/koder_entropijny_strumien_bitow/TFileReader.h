#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include <iostream>
#include <vector>
#include <math.h>
#include "TImage.h"
#pragma warning(disable : 4996)
class TFileReader
{
private:
  FILE* m_pfFile; // zmienna przechowuj¹ca plik
  int m_iWidth;
  int m_iHeight;
  string m_sFilename;
  int m_iCounter;
  int OneAmount;
  int ZeroAmount;
  typedef struct image_buffor  //struktura do przechowywania danych
  {
    int             iWidth_;
    int             iHeight_;
    int             itotal_;
    unsigned char* buf_;
  }image_buffor;
  image_buffor m_ibBuffor;
public:
  TFileReader(int iWidth, int iHeight, string sFileName);
  TImage* ReadFrame();
  void PrintProbability();
};

