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
//#include "TAns.h"
#include "UnitTestAns.cpp"
//void TestAns(TAns* ans, int iAmountTestValue);
int main()
{
  srand(time(NULL));
  TOutputBitstream* bit_stream = new TOutputBitstream();
  TInputBitstream* load_bit_stream = new TInputBitstream();

  /* Implementacja testów */
  int iAmountTest =10;
  TAns* ans = new TAns(16, 2,16);
  TestAns( ans, iAmountTest);  // Testowanie poprawności działania ANS
 

}


