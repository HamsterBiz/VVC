#include "TAns.h"

TAns::TAns(int iL, int ib, int iXstate)
{
  m_iL = iL;
  m_ib = ib;
  m_iUs=0;
  m_iS=0;
  m_iXq=0;
  m_iXstate= iXstate;
}

void TAns::Code(int iP1, int s)
{
      //cerr <<"s"<< int(s)<< " " ;
      //m_uiTest1.push_back(s); //bufory przechowywaæ na zewn¹trz
      m_iUs = 0;
      if (s == 0) m_iUs = m_ib * (m_iL - iP1);
      else m_iUs = m_ib * iP1;
      while (m_iXstate >= m_iUs)
      {
        m_uiCodeValue.push_back(m_iXstate % m_ib);
       // cerr << m_iXstate % m_ib << " ";
        m_iXstate = m_iXstate / m_ib;
      }
      if (s == 0) m_iXstate = floor(((m_iXstate + 1) * m_iL - 1) / (m_iL - iP1));
      else m_iXstate = floor((m_iXstate * m_iL / iP1));
}//zbedne flory

int TAns::Decode(int iP1)
{
 
  m_iS = floor(((m_iXstate + 1) * iP1  - 1) / m_iL) -floor((m_iXstate * iP1  - 1) / m_iL); //  s = floor(((x + 1) * dProbZero_ - 1) / m_iL) - floor((x * dProbZero_ - 1) / m_iL);
  m_iXq = floor((m_iXstate * iP1 - 1) / m_iL + 1);
  if (m_iS == 0) m_iXstate = m_iXstate - m_iXq;
  else m_iXstate = m_iXq;

      while (m_iXstate < m_iL)
      {
        if (!m_uiCodeValue.empty())
        {
          //cerr << m_uiCodeValue.back() << " ";
          m_iXstate = m_iXstate * m_ib + m_uiCodeValue.back();
          m_uiCodeValue.pop_back();
        }
        else break;
      }
     // cerr << "s" << m_iS << " ";
      return m_iS;
      
}

void TAns::Test(int counter)
{
  cerr << endl;
  cerr << endl;
  //cerr << "rozmiar1 : " << m_uiTest1.size() << " rozmiar2 : " << m_uiTest2.size() << endl;
 // int iSizeVector = m_uiTest1.size() - 1;
  //for (unsigned i = 0; i <= iSizeVector; i++)
  //{
 //   if (m_uiTest1[i] == m_uiTest2[iSizeVector - i]) cerr << "t";
  //  else
 //   {
   //   cerr << "Error at i: " <<i<<" iSizeVector-i : "<< iSizeVector - i<< endl;
   //   cin.get();
   // }
 // }
}

