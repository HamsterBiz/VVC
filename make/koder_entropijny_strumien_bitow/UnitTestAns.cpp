#include "TAns.h"
static void TestAns(TAns* ans,int iAmountTestValue)
{
  bool bCorrect = true;
  int temp = 0;
  vector<uint8_t> m_uiTest1; // vektory do przechowywania zmiennych w celu przetestowania poprawnosci dzia³ania programu
  vector<uint8_t> m_uiTest2;
  for (int i = 0; i < iAmountTestValue; i++)
  {
    m_uiTest1.push_back(rand() % 2 + 0);
  }
  //int size = m_uiTest1.size() - 1;
  for (int i = 0; i < m_uiTest1.size(); i++)
  {
    ans->Code(4, m_uiTest1[i]);
    //m_uiTest1.pop_back();
  }
  cerr << "dekodowanie" << endl;
  for (int i = 0; i < m_uiTest1.size(); i++)
  {
    temp = ans->Decode(4);
    m_uiTest2.push_back(temp);
  }

  int iSizeVector = m_uiTest1.size() - 1;
  for (unsigned i = 0; i <= iSizeVector; i++)
  {
    if (m_uiTest1[i] == m_uiTest2[iSizeVector - i]) ;
    else
    {
      bCorrect = false;
    }
  }
  if (bCorrect == true)
  {
    cerr << "ANS works fine" << endl;
  }
  else
  {
    cerr << "ANS is not working properly" << endl;
  }
}