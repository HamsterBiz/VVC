//Program zamieniający liczby dziesiętne na ciąg bitów
//
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
using namespace std;

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
  load_bit_stream->Read(1);
}


