#include "stdint.h"
#include <inttypes.h>
#include <iostream>
using namespace std;
#include <ctime>
#include <vector>
#include "TOutputBitstream.h"
#include "TInputBitstream.h"
#include "UnitTestAns.cpp"
#include "TFileReader.h"
int main()
{
  srand(time(NULL));
  TOutputBitstream* bit_stream = new TOutputBitstream();
  TInputBitstream* load_bit_stream = new TInputBitstream();
  int iSizeBeforeEncoding = 0;
  int iSizeAfterEncoding = 0;
  /* Implementacja testów */
  TestAns();  // Testowanie poprawności działania ANS (UnitTestAns.cpp)
  //-------------------------------------------------------------------

  
  TFileReader* pFileReader = new TFileReader(176, 144, "foreman_176x144_qcif.yuv");
  TImage* pImage = pFileReader->ReadFrame();

  //pFileReader->PrintProbability();

  TAns* ans2 = new TAns(16, 2, 16);
  uint8_t uiPixelValue;
  int uiP1 = ((pFileReader->GetOneAmount() / pFileReader->GetAll()))*16;
  for (uint16_t y = 0; y < pImage->GetHeight(); y++)
    for (uint16_t x = 0; x < pImage->GetWidth(); x++)
    {
      uiPixelValue = pImage->GetValueAt(y, x);
      for (uint32_t i = 0; i < 8; i++)
      {
        iSizeBeforeEncoding++;
      
        uint8_t uiBit = uiPixelValue & 0x01;
        ans2->Code(uiP1, uiBit);
        uiPixelValue = uiPixelValue >> 1;
      }
    }
  TImage* pDecodeImage = new TImage(nullptr, pImage->GetWidth(), pImage->GetHeight());
  iSizeAfterEncoding = ans2->GetBitAmout();
  cerr << "Rozmiary: " << endl;
  cerr << "Przed kodowaniem: "<< iSizeBeforeEncoding <<endl;
  cerr << "Po kodowaniu: "<< iSizeAfterEncoding <<endl;

  for (uint16_t y = 0; y < pImage->GetHeight(); y++)
    for (uint16_t x = 0; x < pImage->GetWidth(); x++)
    {
      uint8_t uiPixelValue = 0;
      for (uint32_t i = 0; i < 8; i++)
      {
        uint8_t uiBit = ans2->Decode(uiP1);
        //cerr << int(uiBit) << endl;
        uiPixelValue = (uiPixelValue << 1) | uiBit;
      }
     // cerr << int(uiPixelValue) << endl;
     // cin.get();
      pDecodeImage->InsertValueAt(y, x, uiPixelValue);
    }
  cerr << "code" << endl;
  cerr << int(pImage->GetValueAt(0, 0)) << endl;
  cerr << int(pImage->GetValueAt(0, 1)) << endl;
  cerr << int(pImage->GetValueAt(0, 2)) << endl;
  cerr << int(pImage->GetValueAt(0, 3)) << endl;
  cerr << int(pImage->GetValueAt(215, 172)) << endl;
  cerr << int(pImage->GetValueAt(215, 173)) << endl;
  cerr << int(pImage->GetValueAt(215, 174)) << endl;
  cerr << int(pImage->GetValueAt(215, 175)) << endl;

  cerr << "decode" << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 0)) << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 1)) << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 2)) << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 3)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 172)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 173)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 174)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 175)) << endl;
  
  pImage->DCT8x8();
  pImage->IDCT8x8();
}


