#pragma once
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
#include <fstream>
using namespace std;
class LoadBitStream
{
private:
  uint16_t temp_;
  uint16_t stream_[255] = { 0 };
  uint16_t stream_test_[255];
  int index_stream_;
  char buffer[16];
public:
  void Read(int n);

};

