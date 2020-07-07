#pragma once
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
class TInputBitstream
{
private:
  vector<uint8_t> m_fifo;
  uint8_t im_uiHeldBits;
  uint32_t uiNumOfBitsTemp;
public:
  void Read();
  void Test(uint8_t uiTestBits, int iCounter);
};

