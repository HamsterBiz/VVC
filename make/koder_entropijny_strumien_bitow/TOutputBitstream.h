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
  vector<uint8_t> m_test1;
  vector<uint8_t> m_test2;
  uint8_t im_uiHeldBits;
  uint8_t m_uiHeldBits;         //Bufor na nie wpe³ni wype³nione bajty
  uint32_t m_uiNumOfHeldBits;   //Liczba bitów w trzymanym bajcie
  int iMask_;
  int iMaskAdd_;
  uint8_t im_uiTemp;
  double dProbZero_;
  int x = 16;
  int m_iL = 16;//16
  int m_ib = 2;
  int m_iUs = 0;
  int s;
  int xq;
  int iLoadBit;
  int iAmuntBit = 0;
  int iAmountSaveValue = 0;
  uint8_t bits_to_save = 0;
  int mask_tem = 1;
  int counter = 0;
  int counter2 = 0;
  uint8_t im_uResultSave = 0;
  int iCounterResult = 0;
public:
  TOutputBitstream();
  ~TOutputBitstream()=default;
  void PutN(uint32_t uiNumOfBits, uint32_t uiBits); 
  void PutN8Bit(uint8_t uiNumOfBits, uint8_t uiBits); //Funkcja dodaj¹ca wartoœci do wektora bezpoœrednio z obrazu (8 bitów)
  unsigned GetSizeBuffor();
  uint8_t GetValueFromVector(int iId);
  void CodeSymbols(); // Kodowanie ANS
  void DecodeSymbols(); //Dekodowanie ANS
  void CheckTheCodingIsCorrect(); //Testowanie ANS
  //void Read(int n);             //Funkcja wczytuj¹ca z pliku n bitów i wpisuj¹ca je do zmiennej uint16_t* stream_test_[255] (zmienna stworzona do testowania - w przysz³oœci zostanie usuniêta)
  void Write();             //Funkcja zapisuj¹ca do pliku n bitów ze zmiennej   uint16_t* stream_[255] 
};


