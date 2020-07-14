#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include <iostream>
#include <vector>
#pragma warning(disable : 4996)

class TInputImage
{
private:
  FILE* m_fFile; // zmienna przechowuj¹ca plik
  int m_iAmountFrame;
  int m_iWidth;
  int m_iHeight;
  string m_sFilename;
  //int m_iLumaAmount;
  //int m_iChromaAmount;
  int m_iCounter;
 // bool m_bLuma;
  //bool m_bChroma;
  vector<uint8_t> m_uiImageValues;
  typedef struct image_buffor  //struktura do przechowywania danych
  {
    int             iWidth_;
    int             iHeight_;
    int             itotal_;
    unsigned char* buf_;
  }image_buffor;
  image_buffor m_ibBuffor;
public:
  TInputImage(int iWidth, int iHeight, int iAmountFrame, string sFileName);
  int GetCounter();
  void ReadVideo();
  vector<uint8_t>* GetVectorImage();
};

