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
  vector<uint8_t> m_fifo;       //buffor n wpe³ni wype³nione bajty
  vector<uint8_t> m_fifo2;       //buffor n wpe³ni wype³nione bajty
  vector<int> m_iFifoCode;
  uint8_t im_uiHeldBits;
  uint8_t m_uiHeldBits;         //Bufor na nie wpe³ni wype³nione bajty
  uint32_t m_uiNumOfHeldBits;   //Liczba bitów w trzymanym bajcie
  int iMask_;
  int iMaskAdd_;
  uint8_t im_uiTemp;

public:
  TOutputBitstream();
  ~TOutputBitstream()=default;
  void PutN(uint32_t uiNumOfBits, uint32_t uiBits); 
  void PutN8Bit(uint8_t uiNumOfBits, uint8_t uiBits); //Funkcja dodaj¹ca wartoœci do wektora bezpoœrednio z obrazu (8 bitów)
  vector<int>* SplitIntoBits(vector<uint8_t>* VectorToSplit);
  unsigned GetSizeBuffor();
  uint8_t GetValueFromVector(int iId);
  //void Read(int n);             //Funkcja wczytuj¹ca z pliku n bitów i wpisuj¹ca je do zmiennej uint16_t* stream_test_[255] (zmienna stworzona do testowania - w przysz³oœci zostanie usuniêta)
  void Write();             //Funkcja zapisuj¹ca do pliku n bitów ze zmiennej   uint16_t* stream_[255] 
};


