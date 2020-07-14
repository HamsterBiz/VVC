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
#include "TAns.h"

int main()
{
  TOutputBitstream* bit_stream = new TOutputBitstream();
  TInputBitstream* load_bit_stream = new TInputBitstream();

  /* Implementacja testów */
  srand(time(NULL));
  int iAmountTest =10001;
  vector<uint32_t> NumBit;
  vector<uint32_t> ValBit;
  /* Implementacja testów   */
 // ValBit.push_back(89);
 // ValBit.push_back(122);
  for (int i = 0; i < iAmountTest; i++)
 {
  // NumBit.push_back((std::rand() % 32) + 0);
  // ValBit.push_back((std::rand() % 4294967296) + 0);
  }

  for (int i = 0; i < iAmountTest; i++)
  {
   // cerr << rand() % 2 + 0 << endl;
   // bit_stream->PutN(ValBit[i], NumBit[i]);
  }
  // bit_stream->PutN(323900928, 8);
  // bit_stream->PutN(35329024224,8);
   //bit_stream->PutN(352329024224, 8);
  //bit_stream->PutN(192, 8);
  //bit_stream->Write();
  //load_bit_stream->Read();
  /*  */
  //int iTemp = int(bit_stream->GetSizeBuffor());
  //cerr << "testowanie" << endl;
 // int counter = 0;
 // for (int i = 0; i < iTemp; i++)
 // {
 //   load_bit_stream->Test(bit_stream->GetValueFromVector(i), i);
 //   counter++;
 // }
  //cerr << "symbole" << endl;TAns
  TAns* ans = new TAns(16, 2);
  for (int i = 0; i < iAmountTest; i++)
  {
    ans->Code(4, rand() % 2 + 0);
  }
  cerr << endl;
  cerr << "dekoduje" << endl;
  for (int i = 0; i < iAmountTest; i++)
  {
    ans->Decode(4);
  }
  ans->Test(iAmountTest);
  //bit_stream->CodeSymbols();
 // bit_stream->DecodeSymbols();
 // bit_stream->CheckTheCodingIsCorrect();
  /* ------------------------------------------------------------- */
}


