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
#include "TPrediction.h"
#include "TContextModeling.h"
int main()
{
  //srand(time(NULL));
  TOutputBitstream* bit_stream = new TOutputBitstream();
  TInputBitstream* load_bit_stream = new TInputBitstream();
  int iSizeBeforeEncoding = 0;
  int iSizeAfterEncoding = 0;
  /* Implementacja testów */
  TestAns();  // Testowanie poprawności działania ANS (UnitTestAns.cpp)
  //-------------------------------------------------------------------
  int iZero = 0;
  int iOne = 0;

  TFileReader* pFileReader = new TFileReader(176, 144, "foreman_176x144_qcif.yuv");
  TImage* pImage = pFileReader->ReadFrame();
  //
  //pImage->ZigZag4x4();
  TPrediction* prediction = new TPrediction(pImage->GetImageMatrix(), pImage->GetWidth(), pImage->GetHeight(), 8);
  vector<TContextModeling*> ProbabilityVectorLeft;
  vector<TContextModeling*> ProbabilityVectorTop;
  vector<TContextModeling*> ProbabilityVectorCorner;
  int** matrix;
  int** Matrix2;
  unsigned SizeZigZag;
  int uiPixelValue;
  bool negative = false;
  int maks = 0;
  int min = 0;
  for (int i = 0; i < 16; i++)
  {
    ProbabilityVectorLeft.push_back(new TContextModeling(256));
    ProbabilityVectorTop.push_back(new TContextModeling(256));
    ProbabilityVectorCorner.push_back(new TContextModeling(256));
  }
  TAns* ansLeft = new TAns(256, 2, 16);
  TAns* ansTop = new TAns(256, 2, 16);
  TAns* ansCorner = new TAns(256, 2, 16);
  int XBlock = pImage->GetWidth() / 8;
  int YBlock = pImage->GetHeight() / 8;
  int iQuantizationFactor = 10;
  int iZeroAmount = 0;
  int iAmountDecodeValue = 0;
  int iAmountDecodeValueL = 0;
  int iAmountDecodeValueT = 0;
  cerr << 0 / 8 << "dzielenie zera" << endl;
  cerr << "ilosc bloków X: " << XBlock << " ilosc bloków Y:" << YBlock << endl;
  //prediction->IncrementHeight();
  prediction->IncrementHeight();
  prediction->IncrementWidth();
  prediction->IncrementWidth();
  prediction->PredictionMotion();
 // prediction->IncrementWidth();
 // prediction->PredictionMotion();
 // prediction->IncrementWidth();
 // prediction->PredictionMotion();
  /* DZIALAJACE KODOWANIE I DEKODOWANIE
  cerr << "ilosc bloków X: " << XBlock << " ilosc bloków Y:" << YBlock << endl;
  for (int k = 0; k < YBlock; k++)//Yblock
  {
    for (int l = 0; l < XBlock; l++)//Xblock
    {

      prediction->PredicitionLeftCorner();
      matrix = prediction->GetLeftCorner();
      pImage->DCT8x8(matrix);
      // cerr << endl;
      Matrix2 = pImage->GetDCTMatrix();
      pImage->ZigZag4x4(Matrix2);
      // pImage->IDCT8x8();
      SizeZigZag = pImage->GetSizeZigZag();
      //cerr << "ZigZagSize:" << pImage->GetSizeZigZag() << endl;
      //cin.get();
      for (unsigned y = 0; y < SizeZigZag; y++)
      {
        if (y == 0)// pierwszy symbol > 0
        {
          uiPixelValue = pImage->GetValueZigZag(y);
          uiPixelValue /= iQuantizationFactor;
          cerr << uiPixelValue << " ";
          if (maks < uiPixelValue) maks = uiPixelValue;
          if (min > uiPixelValue) min = uiPixelValue;
          if (uiPixelValue < 0)
          {
            uiPixelValue = abs(uiPixelValue);
            negative = true;
          }

          for (uint32_t i = 0; i < 12; i++)
          {
            uint8_t uiBit = uiPixelValue & 0x01;
            ProbabilityVectorCorner[i]->ChangeProbabilityCode(uiBit);
            ansCorner->Code(ProbabilityVectorCorner[i]->GetProbabilityOfOne(), uiBit);
            uiPixelValue = uiPixelValue >> 1;
          }
          if (negative == true)
          {
            ProbabilityVectorCorner[12]->ChangeProbabilityCode(1);
            ansCorner->Code(ProbabilityVectorCorner[12]->GetProbabilityOfOne(), 1);

            negative = false;
          }
          else
          {
            ProbabilityVectorCorner[12]->ChangeProbabilityCode(0);
            ansCorner->Code(ProbabilityVectorCorner[12]->GetProbabilityOfOne(), 0);
          }
        }
        else //sprawdzanie kolejnych symboli
        {
          uiPixelValue = pImage->GetValueZigZag(y);
          uiPixelValue /= iQuantizationFactor;
          cerr << uiPixelValue << " ";
          if (uiPixelValue == 0)
          {
            iZeroAmount++;
          }
          else
          {
            for (uint32_t i = 0; i < 12; i++)//kodowanie liczby zer
            {
              uint8_t uiBit = iZeroAmount & 0x01;
              ProbabilityVectorCorner[i]->ChangeProbabilityCode(uiBit);
              ansCorner->Code(ProbabilityVectorCorner[i]->GetProbabilityOfOne(), uiBit);
              iZeroAmount = iZeroAmount >> 1;
            }
            ProbabilityVectorCorner[12]->ChangeProbabilityCode(0);
            ansCorner->Code(ProbabilityVectorCorner[12]->GetProbabilityOfOne(), 0);
            iZeroAmount = 0;
            if (uiPixelValue < 0)
            {
              uiPixelValue = abs(uiPixelValue);
              negative = true;
            }
            for (uint32_t i = 0; i < 12; i++)//kodowanie kolejnej wartosci po 0
            {
              uint8_t uiBit = uiPixelValue & 0x01;
              ProbabilityVectorCorner[i]->ChangeProbabilityCode(uiBit);
              ansCorner->Code(ProbabilityVectorCorner[i]->GetProbabilityOfOne(), uiBit);
              uiPixelValue = uiPixelValue >> 1;
            }
            if (negative == true)
            {
              ProbabilityVectorCorner[12]->ChangeProbabilityCode(1);
              ansCorner->Code(ProbabilityVectorCorner[12]->GetProbabilityOfOne(), 1);

              negative = false;
            }
            else
            {
              ProbabilityVectorCorner[12]->ChangeProbabilityCode(0);
              ansCorner->Code(ProbabilityVectorCorner[12]->GetProbabilityOfOne(), 0);
            }
          }
        }
      }

      //}

      if (iZeroAmount > 0)
      {
        for (uint32_t i = 0; i < 12; i++)//kodowanie liczby zer
        {
          uint8_t uiBit = iZeroAmount & 0x01;
          ProbabilityVectorCorner[i]->ChangeProbabilityCode(uiBit);
          ansCorner->Code(ProbabilityVectorCorner[i]->GetProbabilityOfOne(), uiBit);
          iZeroAmount = iZeroAmount >> 1;
        }
        ProbabilityVectorCorner[12]->ChangeProbabilityCode(0);
        ansCorner->Code(ProbabilityVectorCorner[12]->GetProbabilityOfOne(), 0);


      }
      iZeroAmount = 0;

      cerr << endl;
      pImage->ClearVector();
      ProbabilityVectorCorner[13]->ChangeProbabilityCode(0);
      ansCorner->Code(ProbabilityVectorCorner[13]->GetProbabilityOfOne(), 0);
      ProbabilityVectorCorner[14]->ChangeProbabilityCode(0);
      ansCorner->Code(ProbabilityVectorCorner[14]->GetProbabilityOfOne(), 0);
      // cerr << "ilosc bitow"<<endl;
      cerr << "corner: " << ansCorner->GetBitAmout() << endl;


      prediction->PredictionLeftToRight();
      matrix = prediction->GetLeftToRight();
      pImage->DCT8x8(matrix);
      cerr << endl;
      Matrix2 = pImage->GetDCTMatrix();
      pImage->ZigZag4x4(Matrix2);
      //pImage->IDCT8x8();
      SizeZigZag = pImage->GetSizeZigZag();
      for (unsigned y = 0; y < SizeZigZag; y++)
      {
        if (y == 0)// pierwszy symbol > 0
        {
          uiPixelValue = pImage->GetValueZigZag(y);
          uiPixelValue /= iQuantizationFactor;
          cerr << uiPixelValue << " ";
          if (maks < uiPixelValue) maks = uiPixelValue;
          if (min > uiPixelValue) min = uiPixelValue;
          if (uiPixelValue < 0)
          {
            uiPixelValue = abs(uiPixelValue);
            negative = true;
          }

          for (uint32_t i = 0; i < 12; i++)
          {
            uint8_t uiBit = uiPixelValue & 0x01;
            ProbabilityVectorLeft[i]->ChangeProbabilityCode(uiBit);
            ansLeft->Code(ProbabilityVectorLeft[i]->GetProbabilityOfOne(), uiBit);
            uiPixelValue = uiPixelValue >> 1;
          }
          if (negative == true)
          {
            ProbabilityVectorLeft[12]->ChangeProbabilityCode(1);
            ansLeft->Code(ProbabilityVectorLeft[12]->GetProbabilityOfOne(), 1);

            negative = false;
          }
          else
          {
            ProbabilityVectorLeft[12]->ChangeProbabilityCode(0);
            ansLeft->Code(ProbabilityVectorLeft[12]->GetProbabilityOfOne(), 0);
          }
        }
        else //sprawdzanie kolejnych symboli
        {
          uiPixelValue = pImage->GetValueZigZag(y);
          uiPixelValue /= iQuantizationFactor;
          cerr << uiPixelValue << " ";
          if (uiPixelValue == 0)
          {
            iZeroAmount++;
          }
          else
          {
            for (uint32_t i = 0; i < 12; i++)//kodowanie liczby zer
            {
              uint8_t uiBit = iZeroAmount & 0x01;
              ProbabilityVectorLeft[i]->ChangeProbabilityCode(uiBit);
              ansLeft->Code(ProbabilityVectorLeft[i]->GetProbabilityOfOne(), uiBit);
              iZeroAmount = iZeroAmount >> 1;
            }
            ProbabilityVectorLeft[12]->ChangeProbabilityCode(0);
            ansLeft->Code(ProbabilityVectorLeft[12]->GetProbabilityOfOne(), 0);
            iZeroAmount = 0;

            if (uiPixelValue < 0)
            {
              uiPixelValue = abs(uiPixelValue);
              negative = true;
            }
            for (uint32_t i = 0; i < 12; i++)//kodowanie kolejnej wartosci po 0
            {
              uint8_t uiBit = uiPixelValue & 0x01;
              ProbabilityVectorLeft[i]->ChangeProbabilityCode(uiBit);
              ansLeft->Code(ProbabilityVectorLeft[i]->GetProbabilityOfOne(), uiBit);
              uiPixelValue = uiPixelValue >> 1;
            }
            if (negative == true)
            {
              ProbabilityVectorLeft[12]->ChangeProbabilityCode(1);
              ansLeft->Code(ProbabilityVectorLeft[12]->GetProbabilityOfOne(), 1);

              negative = false;
            }
            else
            {
              ProbabilityVectorLeft[12]->ChangeProbabilityCode(0);
              ansLeft->Code(ProbabilityVectorLeft[12]->GetProbabilityOfOne(), 0);
            }
          }
        }
      }

      //}

      if (iZeroAmount > 0)
      {
        for (uint32_t i = 0; i < 12; i++)//kodowanie liczby zer
        {
          uint8_t uiBit = iZeroAmount & 0x01;
          ProbabilityVectorLeft[i]->ChangeProbabilityCode(uiBit);
          ansLeft->Code(ProbabilityVectorLeft[i]->GetProbabilityOfOne(), uiBit);
          iZeroAmount = iZeroAmount >> 1;
        }
        ProbabilityVectorLeft[12]->ChangeProbabilityCode(0);
        ansLeft->Code(ProbabilityVectorLeft[12]->GetProbabilityOfOne(), 0);


      }
      iZeroAmount = 0;
      cerr << endl;
      pImage->ClearVector();
      ProbabilityVectorLeft[13]->ChangeProbabilityCode(1);
      ansLeft->Code(ProbabilityVectorLeft[13]->GetProbabilityOfOne(), 1);
      ProbabilityVectorLeft[14]->ChangeProbabilityCode(0);
      ansLeft->Code(ProbabilityVectorLeft[14]->GetProbabilityOfOne(), 0);
      // cerr << "ilosc bitow" << endl;
      cerr << "left: " << ansLeft->GetBitAmout() << endl;


      prediction->PredictionTopToBottom();
      matrix = prediction->GetTopToBottom();
      pImage->DCT8x8(matrix);
      cerr << endl;
      Matrix2 = pImage->GetDCTMatrix();
      pImage->ZigZag4x4(Matrix2);
      SizeZigZag = pImage->GetSizeZigZag();

      for (unsigned y = 0; y < SizeZigZag; y++)
      {
        if (y == 0)// pierwszy symbol > 0
        {
          uiPixelValue = pImage->GetValueZigZag(y);
          uiPixelValue /= iQuantizationFactor;
          cerr << uiPixelValue << " ";
          if (maks < uiPixelValue) maks = uiPixelValue;
          if (min > uiPixelValue) min = uiPixelValue;
          if (uiPixelValue < 0)
          {
            uiPixelValue = abs(uiPixelValue);
            negative = true;
          }

          for (uint32_t i = 0; i < 12; i++)
          {
            uint8_t uiBit = uiPixelValue & 0x01;
            ProbabilityVectorTop[i]->ChangeProbabilityCode(uiBit);
            ansTop->Code(ProbabilityVectorTop[i]->GetProbabilityOfOne(), uiBit);
            uiPixelValue = uiPixelValue >> 1;
          }
          if (negative == true)
          {
            ProbabilityVectorTop[12]->ChangeProbabilityCode(1);
            ansTop->Code(ProbabilityVectorTop[12]->GetProbabilityOfOne(), 1);

            negative = false;
          }
          else
          {
            ProbabilityVectorTop[12]->ChangeProbabilityCode(0);
            ansTop->Code(ProbabilityVectorTop[12]->GetProbabilityOfOne(), 0);
          }
        }
        else //sprawdzanie kolejnych symboli
        {
          uiPixelValue = pImage->GetValueZigZag(y);
          uiPixelValue /= iQuantizationFactor;
          cerr << uiPixelValue << " ";
          if (uiPixelValue == 0)
          {
            iZeroAmount++;
          }
          else
          {
            for (uint32_t i = 0; i < 12; i++)//kodowanie liczby zer
            {
              uint8_t uiBit = iZeroAmount & 0x01;
              ProbabilityVectorTop[i]->ChangeProbabilityCode(uiBit);
              ansTop->Code(ProbabilityVectorTop[i]->GetProbabilityOfOne(), uiBit);
              iZeroAmount = iZeroAmount >> 1;
            }
            ProbabilityVectorTop[12]->ChangeProbabilityCode(0);
            ansTop->Code(ProbabilityVectorTop[12]->GetProbabilityOfOne(), 0);
            iZeroAmount = 0;
            if (uiPixelValue < 0)
            {
              uiPixelValue = abs(uiPixelValue);
              negative = true;
            }
            for (uint32_t i = 0; i < 12; i++)//kodowanie kolejnej wartosci po 0
            {
              uint8_t uiBit = uiPixelValue & 0x01;
              ProbabilityVectorTop[i]->ChangeProbabilityCode(uiBit);
              ansTop->Code(ProbabilityVectorTop[i]->GetProbabilityOfOne(), uiBit);
              uiPixelValue = uiPixelValue >> 1;
            }
            if (negative == true)
            {
              ProbabilityVectorTop[12]->ChangeProbabilityCode(1);
              ansTop->Code(ProbabilityVectorTop[12]->GetProbabilityOfOne(), 1);

              negative = false;
            }
            else
            {
              ProbabilityVectorTop[12]->ChangeProbabilityCode(0);
              ansTop->Code(ProbabilityVectorTop[12]->GetProbabilityOfOne(), 0);
            }
          }
        }
      }

      //}

      if (iZeroAmount > 0)
      {
        for (uint32_t i = 0; i < 12; i++)//kodowanie liczby zer
        {
          uint8_t uiBit = iZeroAmount & 0x01;
          ProbabilityVectorTop[i]->ChangeProbabilityCode(uiBit);
          ansTop->Code(ProbabilityVectorTop[i]->GetProbabilityOfOne(), uiBit);
          iZeroAmount = iZeroAmount >> 1;
        }
        ProbabilityVectorTop[12]->ChangeProbabilityCode(0);
        ansTop->Code(ProbabilityVectorTop[12]->GetProbabilityOfOne(), 0);


      }
      iZeroAmount = 0;
      cerr << endl;
      pImage->ClearVector();
      ProbabilityVectorTop[13]->ChangeProbabilityCode(1);
      ansTop->Code(ProbabilityVectorTop[13]->GetProbabilityOfOne(), 1);
      ProbabilityVectorTop[14]->ChangeProbabilityCode(1);
      ansTop->Code(ProbabilityVectorTop[14]->GetProbabilityOfOne(), 1);
      //cerr << "ilosc bitow" << endl;
      cerr << "top: " << ansTop->GetBitAmout() << endl;



      if (ansTop->GetBitAmout() < ansLeft->GetBitAmout())
      {
        if (ansCorner->GetBitAmout() < ansTop->GetBitAmout())
        {//corner najmniej bitów
          cerr << "corner" << endl;
          iAmountDecodeValueL = iAmountDecodeValue;
          iAmountDecodeValueT = iAmountDecodeValue;
          delete ansLeft;
          delete ansTop;
          ansLeft = new TAns(ansCorner->GetL(), ansCorner->GetB(), ansCorner->GetXstate(), ansCorner->GetVector());
          ansTop = new TAns(ansCorner->GetL(), ansCorner->GetB(), ansCorner->GetXstate(), ansCorner->GetVector());
          for (int i = 0; i < 16; i++)
          {
            ProbabilityVectorLeft[i]->SetOne(ProbabilityVectorCorner[i]->GetOne());
            ProbabilityVectorLeft[i]->SetZero(ProbabilityVectorCorner[i]->GetZero());
            ProbabilityVectorLeft[i]->SetProbabilityOfOne(ProbabilityVectorCorner[i]->GetProbabilityOfOne());
            ProbabilityVectorTop[i]->SetOne(ProbabilityVectorCorner[i]->GetOne());
            ProbabilityVectorTop[i]->SetZero(ProbabilityVectorCorner[i]->GetZero());
            ProbabilityVectorTop[i]->SetProbabilityOfOne(ProbabilityVectorCorner[i]->GetProbabilityOfOne());
          }
          // TAns* ansCorner = new TAns(256, 2, 16);
        }
        else//top najmniej bitów
        {
          cerr << "top" << endl;
          delete ansLeft;
          delete ansCorner;
          ansLeft = new TAns(ansTop->GetL(), ansTop->GetB(), ansTop->GetXstate(), ansTop->GetVector());
          ansCorner = new TAns(ansTop->GetL(), ansTop->GetB(), ansTop->GetXstate(), ansTop->GetVector());
          for (int i = 0; i < 16; i++)
          {
            ProbabilityVectorLeft[i]->SetOne(ProbabilityVectorTop[i]->GetOne());
            ProbabilityVectorLeft[i]->SetZero(ProbabilityVectorTop[i]->GetZero());
            ProbabilityVectorLeft[i]->SetProbabilityOfOne(ProbabilityVectorTop[i]->GetProbabilityOfOne());
            ProbabilityVectorCorner[i]->SetOne(ProbabilityVectorTop[i]->GetOne());
            ProbabilityVectorCorner[i]->SetZero(ProbabilityVectorTop[i]->GetZero());
            ProbabilityVectorCorner[i]->SetProbabilityOfOne(ProbabilityVectorTop[i]->GetProbabilityOfOne());
          }
        }
      }
      else
      {
        if (ansCorner->GetBitAmout() < ansLeft->GetBitAmout())
        {//corner najmniej bitów
          cerr << "corner" << endl;
          delete ansLeft;
          delete ansTop;
          ansTop = new TAns(ansCorner->GetL(), ansCorner->GetB(), ansCorner->GetXstate(), ansCorner->GetVector());
          ansLeft = new TAns(ansCorner->GetL(), ansCorner->GetB(), ansCorner->GetXstate(), ansCorner->GetVector());
          for (int i = 0; i < 16; i++)
          {
            ProbabilityVectorLeft[i]->SetOne(ProbabilityVectorCorner[i]->GetOne());
            ProbabilityVectorLeft[i]->SetZero(ProbabilityVectorCorner[i]->GetZero());
            ProbabilityVectorLeft[i]->SetProbabilityOfOne(ProbabilityVectorCorner[i]->GetProbabilityOfOne());
            ProbabilityVectorTop[i]->SetOne(ProbabilityVectorCorner[i]->GetOne());
            ProbabilityVectorTop[i]->SetZero(ProbabilityVectorCorner[i]->GetZero());
            ProbabilityVectorTop[i]->SetProbabilityOfOne(ProbabilityVectorCorner[i]->GetProbabilityOfOne());
          }
        }
        else//left najmniej bitów
        {
          cerr << "left" << endl;
          iAmountDecodeValue = iAmountDecodeValueL;
          iAmountDecodeValueT = iAmountDecodeValueL;
          delete ansTop;
          delete ansCorner;
          ansTop = new TAns(ansLeft->GetL(), ansLeft->GetB(), ansLeft->GetXstate(), ansLeft->GetVector());
          ansCorner = new TAns(ansLeft->GetL(), ansLeft->GetB(), ansLeft->GetXstate(), ansLeft->GetVector());
          for (int i = 0; i < 16; i++)
          {
            ProbabilityVectorCorner[i]->SetOne(ProbabilityVectorLeft[i]->GetOne());
            ProbabilityVectorCorner[i]->SetZero(ProbabilityVectorLeft[i]->GetZero());
            ProbabilityVectorCorner[i]->SetProbabilityOfOne(ProbabilityVectorLeft[i]->GetProbabilityOfOne());
            ProbabilityVectorTop[i]->SetOne(ProbabilityVectorLeft[i]->GetOne());
            ProbabilityVectorTop[i]->SetZero(ProbabilityVectorLeft[i]->GetZero());
            ProbabilityVectorTop[i]->SetProbabilityOfOne(ProbabilityVectorLeft[i]->GetProbabilityOfOne());
          }
        }


      }
      prediction->IncrementWidth();
    }
    prediction->IncrementHeight();
  }
  cerr << "Maks: " << maks << endl;
  cerr << "Min: " << min << endl;

  // pImage->DCT8x8();

   //unsigned SizeZigZag = pImage->GetSizeZigZag();
  cerr << "size Zigzag" << SizeZigZag << endl;

  //vector<int>* Probability = pImage->CalculateProbability(256);
  cerr << "prawd" << endl;
  cerr << "Rozmiar vektora: " << ProbabilityVectorTop.size() << endl;
  for (int i = 0; i < ProbabilityVectorTop.size(); i++)
  {
    cerr << ProbabilityVectorTop[i]->GetProbabilityOfOne() << " "; cerr << ProbabilityVectorTop[i]->GetOne() << " "; cerr << ProbabilityVectorTop[i]->GetZero() << " ";
    cerr << endl;
  }
  cerr << "prawd" << endl;
  uiPixelValue;

  std::fstream file;
  file.open("test.bin", ios::in | ios::out | ios::binary);
  negative = false;
  //TImage* pDecodeImage = new TImage(nullptr, pImage->GetWidth(), pImage->GetHeight());
 // iSizeAfterEncoding = ans2->GetBitAmout();
  cerr << "Rozmiary: " << endl;
  cerr << "Przed kodowaniem: " << pFileReader->GetAll() << endl;
  cerr << "Po kodowaniu: " << iSizeAfterEncoding << endl;
  cerr << endl;
  cerr << endl;
  cerr << endl;
  cerr << endl;
  cerr << endl;
  cerr << endl;
  cerr << endl;
  cerr << "dokodowanie ilosc: " << iAmountDecodeValue << endl;
  cin.get();
  cerr << endl; cerr << endl;
  cerr << endl;
  pImage->ClearVector();
  cerr << "ilosc bitow" << endl;
  bool Negative = false;
  int temppp;
  int zeros = 0;
  for (unsigned y = 0; y < 600; y++)
  {
    temppp = ansTop->Decode(ProbabilityVectorTop[14]->GetProbabilityOfOne());
    cerr << temppp;
    ProbabilityVectorTop[14]->ChangeProbabilityDecode(temppp);
    temppp = ansTop->Decode(ProbabilityVectorTop[13]->GetProbabilityOfOne());
    cerr << temppp << " ";
    ProbabilityVectorTop[13]->ChangeProbabilityDecode(temppp);
    for (int k = 0; k < 64; k++)
    {
      uiPixelValue = 0;
      for (uint32_t i = 0; i < 13; i++)
      {
        // cerr << "w";
        if (i == 0)
        {
          if (0 != ansTop->Decode(ProbabilityVectorTop[12 - i]->GetProbabilityOfOne()))
          {
            ProbabilityVectorTop[12 - i]->ChangeProbabilityDecode(1);
            Negative = true;
          }
          else  ProbabilityVectorTop[12 - i]->ChangeProbabilityDecode(0);
        }
        else {

          uint8_t uiBit = ansTop->Decode(ProbabilityVectorTop[12 - i]->GetProbabilityOfOne());
          ProbabilityVectorTop[12 - i]->ChangeProbabilityDecode(uiBit);
          uiPixelValue = (uiPixelValue << 1) | uiBit;
        }
      }
      cerr << " ";
      if (Negative == true)
      {
        uiPixelValue = uiPixelValue * (-1);
        Negative = false;
      }

      zeros++;
      if (zeros % 2 != 0)
      {
        if (uiPixelValue == 0)
        {
          k--;
        }
        else
        {
          k += uiPixelValue - 1;
          cerr << "z" << uiPixelValue << " ";
        }
      }
      else cerr << uiPixelValue << " ";

    }
    zeros = 0;
    cerr << endl;
    //cin.get();
  }
  */
}


