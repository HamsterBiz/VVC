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

  /* Implementacja testów */
  
  
  TestAns();  // Testowanie poprawności działania ANS (UnitTestAns.cpp)
 
  //TInputImage* image = new TInputImage(176, 144, 1, "frame1_176x144.yuv");   //Utworzenie obiektu klasu odpowiadającej za wczytanie zdjęcia
  TFileReader* pFileReader = new TFileReader(176, 144, "foreman_176x144_qcif.yuv");
  TImage* pImage = pFileReader->ReadFrame();
  vector<uint8_t>* puiImageValues;
  //image->ReadVideo();
  //puiImageValues = pImage->GetVectorImage();
  //int counter=image->GetCounter();
  vector<int>* iBitsToCode;

  TAns* ans2 = new TAns(16, 2, 16);
  uint8_t uiPixelValue;
  uint32_t uiP1 = 6;
  for (uint16_t y = 0; y < pImage->GetHeight(); y++)
    for (uint16_t x = 0; x < pImage->GetWidth(); x++)
    {
      uiPixelValue = pImage->GetValueAt(y, x);
     // cerr << int(uiPixelValue) << endl;
      //cin.get();
      for (uint32_t i = 0; i < 8; i++)
      {
        uint8_t uiBit = uiPixelValue & 0x01;
        ans2->Code(uiP1, uiBit);
        uiPixelValue = uiPixelValue >> 1;
      }
    }
  TImage* pDecodeImage = new TImage(nullptr, pImage->GetWidth(), pImage->GetHeight());


  for (uint16_t y = 0; y < pImage->GetHeight(); y++)
    for (uint16_t x = 0; x < pImage->GetWidth(); x++)
    {
      uint8_t uiPixelValue = 0;
      for (uint32_t i = 0; i < 8; i++)
      {
        uint8_t uiBit = ans2->Decode(uiP1);
        uiPixelValue = (uiPixelValue << 1) | uiBit;
      }
      pDecodeImage->InsertValueAt(y, x, uiPixelValue);
    }
  cerr << "decode" << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 0)) << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 1)) << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 2)) << endl;
  cerr << int(pDecodeImage->GetValueAt(0, 3)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 172)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 173)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 174)) << endl;
  cerr << int(pDecodeImage->GetValueAt(215, 175)) << endl;
  cerr << "code" << endl;
  cerr << int(pImage->GetValueAt(0, 0)) << endl;
  cerr << int(pImage->GetValueAt(0, 1)) << endl;
  cerr << int(pImage->GetValueAt(0, 2)) << endl;
  cerr << int(pImage->GetValueAt(0, 3)) << endl;
  cerr << int(pImage->GetValueAt(215, 172)) << endl;
  cerr << int(pImage->GetValueAt(215, 173)) << endl;
  cerr << int(pImage->GetValueAt(215, 174)) << endl;
  cerr << int(pImage->GetValueAt(215, 175)) << endl;
}


