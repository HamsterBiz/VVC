#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include <iostream>
#pragma warning(disable : 4996)

class TInputImage
{
private:
  FILE* file_name_; // zmienna przechowuj¹ca plik
  //FILE* file_name_edit_;
  //char* video_name_;
  int amount_frame_;
  int width_;
  int height_;
  typedef struct image_buffor  //struktura do przechowywania danych
  {
    int             iWidth_;
    int             iHeight_;
    int             itotal_;
    unsigned char* buf_;
  }image_buffor;
  image_buffor buffor;
  image_buffor editor;
public:
  TInputImage(int width, int height, int amount_frame);
  void ReadVideo();
};

