//Program zamieniający liczby dziesiętne na ciąg bitów
//
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
using namespace std;
#include <ctime>
#include <vector>
#include "TOutputBitstream.h"
#include "TInputBitstream.h"

int main()
{

  TOutputBitstream* bit_stream = new TOutputBitstream();
  //uint8_t vector_test = 122;
  uint32_t vector_test = 200;
  uint32_t size = 8;
 // bit_stream->PutN(4294000000, size);
 // vector_test = 200;
 // bit_stream->PutN(4026531840, size);
 // vector_test = 100;
  //bit_stream->PutN(4126531840, size);
  //vector_test = 205;
  //bit_stream->PutN(4099931840, size);
  //bit_stream->Write(4);
  //bit_stream->PutN(vector_test, 8);
  //bit_stream->Write(1);

  TInputBitstream* load_bit_stream = new TInputBitstream();

  /* Implementacja testów */
  srand(time(NULL));
  int iAmountTest = 100;
  vector<uint32_t> NumBit;
  vector<uint32_t> ValBit;
  
  for (int i = 0; i < iAmountTest; i++)
  {
    NumBit.push_back((rand() % 32) + 0);
    ValBit.push_back((std::rand() % 2147483647) + 0);
  }
  for (int i = 0; i < iAmountTest; i++)
  {
    bit_stream->PutN(ValBit[i], NumBit[i]);
  }
  bit_stream->Write();
  load_bit_stream->Read();
  int iTemp = int(bit_stream->GetSizeBuffor());
  cerr << "testowanie" << endl;
  int counter = 0;
  for (int i = 0; i < iTemp; i++)
  {
    load_bit_stream->Test(bit_stream->GetValueFromVector(i), i);
    counter++;
  }
  /* ------------------------------------------------------------- */
}


