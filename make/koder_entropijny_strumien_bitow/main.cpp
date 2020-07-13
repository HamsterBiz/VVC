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
  TInputBitstream* load_bit_stream = new TInputBitstream();

  /* Implementacja testów */
  //srand(time(NULL));
  int iAmountTest =2 ;
  vector<uint32_t> NumBit;
  vector<uint32_t> ValBit;
  /* Implementacja testów   */
 // ValBit.push_back(89);
 // ValBit.push_back(122);
 // for (int i = 0; i < iAmountTest; i++)
 // {
 //   NumBit.push_back(8);
//    ValBit.push_back((std::rand() % 255) + 1);
//  }

 // for (int i = 0; i < iAmountTest; i++)
 // {
 //   bit_stream->PutN(ValBit[i], NumBit[i]);
  //}
    bit_stream->PutN(323900928, 8);
   //bit_stream->PutN(3590324224,8);
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
  cerr << "symbole" << endl;


  bit_stream->CodeSymbols();
  bit_stream->DecodeSymbols();
  /* ------------------------------------------------------------- */
}


