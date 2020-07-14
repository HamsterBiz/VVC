#include "stdint.h"
#include <inttypes.h>
#include <iostream>
using namespace std;
#include <ctime>
#include <vector>
#include "TOutputBitstream.h"
#include "TInputBitstream.h"
#include "UnitTestAns.cpp"
#include "TInputImage.h"
int main()
{
  srand(time(NULL));
  TOutputBitstream* bit_stream = new TOutputBitstream();
  TInputBitstream* load_bit_stream = new TInputBitstream();

  /* Implementacja testów */
  int iAmountTest =10;
  TAns* ans = new TAns(16, 2,16);
  TestAns( ans, iAmountTest);  // Testowanie poprawności działania ANS (UnitTestAns.cpp)
 
  //TInputImage* image = new TInputImage(176, 144, 1, "frame1_176x144.yuv");   //Utworzenie obiektu klasu odpowiadającej za wczytanie zdjęcia
  TInputImage* image = new TInputImage(176, 144, 1, "foreman_176x144_qcif.yuv"); 
  vector<uint8_t>* uiImageValues;
  image->ReadVideo();
  uiImageValues = image->GetVectorImage();
  //int counter=image->GetCounter();

  bit_stream->SplitIntoBits(uiImageValues);
 // for (int i = 0; i < counter; i++)
 // {

  //}
  

}


