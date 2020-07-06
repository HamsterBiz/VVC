#pragma once
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
#include <fstream>
using namespace std;
class BitStream
{
private:
  uint16_t temp_;
  uint16_t stream_[255] = { 0 };
  uint16_t stream_test_[255];
  int index_stream_;
  int index_current_stream_;
  int mask_;
  int mask_add_;
public:
  BitStream();
  ~BitStream()=default;
  void PutOne(uint8_t a);
  void PutN(uint8_t a, int n);
  //void Read(int n);             //Funkcja wczytuj�ca z pliku n bit�w i wpisuj�ca je do zmiennej uint16_t* stream_test_[255] (zmienna stworzona do testowania - w przysz�o�ci zostanie usuni�ta)
  void Write(int n);             //Funkcja zapisuj�ca do pliku n bit�w ze zmiennej   uint16_t* stream_[255] 
};

