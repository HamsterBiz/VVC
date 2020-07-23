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
  TAns(int iL, int ib, int iXstate);
  void Code(int iP1, int s);
  int Decode(int iP1);
  int GetBitAmout();
  void Save();
private:
  int m_iL;//16
  int m_ib;
  int m_iUs;
  int m_iS;
  int m_iXq;
  int m_iXstate;
  vector<int> m_uiCodeValue; // vektor do zapisania stanu kodera
};

