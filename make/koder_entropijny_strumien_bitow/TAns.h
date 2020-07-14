#pragma once
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
class TAns
{
public:
  TAns(int iL, int ib);
  void Code(int iP1, int s);
  void Decode(int iP1);
  void Test(int counter);
private:
  int m_iL;//16
  int m_ib;
  int m_iUs;
  int m_iS;
  int m_iXq;
  int m_iXstate;
  vector<int> m_uiCodeValue; // vektor do zapisania stanu kodera
  vector<uint8_t> m_uiTest1; // vektory do przechowywania zmiennych w celu przetestowania poprawnosci dzia³ania programu
  vector<uint8_t> m_uiTest2;
};

