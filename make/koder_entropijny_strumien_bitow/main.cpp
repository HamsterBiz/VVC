//Program zamieniający liczby dziesiętne na ciąg bitów
//
#include "stdint.h"
#include <inttypes.h>
#include <iostream>
using namespace std;

#include "BitStream.h"
#include "LoadBitStream.h"

int main()
{

  BitStream* bit_stream = new BitStream();
  uint8_t vector_test = 122;

  bit_stream->PutN(vector_test,8);
  vector_test = 200;
  bit_stream->PutN(vector_test, 8);
  vector_test = 100;
  bit_stream->PutN(vector_test, 8);
  vector_test = 205;
  bit_stream->PutN(vector_test, 8);
  bit_stream->Write(2);
  //bit_stream->PutN(vector_test, 8);
  //bit_stream->Write(1);
  LoadBitStream* load_bit_stream = new LoadBitStream();
  load_bit_stream->Read(1);
}


