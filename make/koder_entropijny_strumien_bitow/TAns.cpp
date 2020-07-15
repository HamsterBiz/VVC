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
      m_iUs = 0;
      if (s == 0) m_iUs = m_ib * (m_iL - iP1);
      else m_iUs = m_ib * iP1;
      while (m_iXstate >= m_iUs)
      {
        m_uiCodeValue.push_back(m_iXstate % m_ib);
        m_iXstate = m_iXstate / m_ib;
      }
      if (s == 0) m_iXstate = floor(((m_iXstate + 1) * m_iL - 1) / (m_iL - iP1));
      else m_iXstate = floor((m_iXstate * m_iL / iP1));
}

int TAns::Decode(int iP1)
{
  m_iS = floor(((m_iXstate + 1) * iP1  - 1) / m_iL) -floor((m_iXstate * iP1  - 1) / m_iL); 
  m_iXq = floor((m_iXstate * iP1 - 1) / m_iL + 1);
  if (m_iS == 0) m_iXstate = m_iXstate - m_iXq;
  else m_iXstate = m_iXq;

      while (m_iXstate < m_iL)
      {
        if (!m_uiCodeValue.empty())
        {
          m_iXstate = m_iXstate * m_ib + m_uiCodeValue.back();
          m_uiCodeValue.pop_back();
        }
        else break;
      }
      return m_iS;
      
}

int TAns::GetBitAmout()
{
  return m_uiCodeValue.size();
}


