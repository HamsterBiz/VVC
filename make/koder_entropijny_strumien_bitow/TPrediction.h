#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#include <iostream>
class TPrediction
{
private:
  int** m_piImageMatrix;
  int** m_piPredictionMatrix;
  int** m_piLeftToRight;
  int** m_piTopToBottom;
  int** m_piLeftCorner;
  int** m_piMotion;
  int m_iMotionVectorX;
  int m_iMotionVectorY;
  int m_iMotionValue;
  int m_iWidth;
  int m_iHeight;
  int m_iActualWidth;
  int m_iActualHeight;
  int m_iBlockSize;
public:
  TPrediction(int** piImageMatrix, int iWidth, int iHeight, int iBlockSize);
  void PredictionLeftToRight();
  void PredictionTopToBottom();
  void PredicitionLeftCorner();
  void PredictionMotion();
  int** GetLeftToRight();
  int** GetTopToBottom();
  int** GetLeftCorner();
  void IncrementHeight();
  void IncrementWidth();
  int GetMotionValue();
  int GetMotionX();
  int GetMotionY();
  int** PredictionMotion(int x, int y);


};

