#pragma once
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class TOutputBitstream
{
private:
  vector<uint8_t> m_fifo;       //buffor n wpe�ni wype�nione bajty
  vector<uint8_t> m_fifo2;       //buffor n wpe�ni wype�nione bajty
  uint8_t im_uiHeldBits;
  uint8_t m_uiHeldBits;         //Bufor na nie wpe�ni wype�nione bajty
  uint32_t m_uiNumOfHeldBits;   //Liczba bit�w w trzymanym bajcie
  int iMask_;
  int iMaskAdd_;
  double dProbZero_;
public:
  TOutputBitstream();
  ~TOutputBitstream()=default;
  void PutN(uint32_t uiNumOfBits, uint32_t uiBits);
  unsigned GetSizeBuffor();
  uint8_t GetValueFromVector(int iId);
  void CodeSymbols();
  void DecodeSymbols();
  //void Read(int n);             //Funkcja wczytuj�ca z pliku n bit�w i wpisuj�ca je do zmiennej uint16_t* stream_test_[255] (zmienna stworzona do testowania - w przysz�o�ci zostanie usuni�ta)
  void Write();             //Funkcja zapisuj�ca do pliku n bit�w ze zmiennej   uint16_t* stream_[255] 
};


