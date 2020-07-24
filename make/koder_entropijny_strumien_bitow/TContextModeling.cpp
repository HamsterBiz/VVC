
#include "TContextModeling.h"

TContextModeling::TContextModeling(int iL)
{
  m_iProbabilityOfOne = 1;
  m_iL = iL;
  m_iOne = 0;
  m_iZero = 0;
}

void TContextModeling::SaveProbability(int iProbabilityOfOne, int iOne, int iZero)
{
  m_iProbabilityOfOne = iProbabilityOfOne;
  m_iOne = iOne;
  m_iZero = iZero;
}

void TContextModeling::ChangeProbabilityCode(int iBit)
{
  if (iBit == 0)
  {
    m_iZero++;
  }
  else m_iOne++;
  m_iProbabilityOfOne = (m_iOne / (m_iZero+ m_iOne)) * m_iL;
}

void TContextModeling::ChangeProbabilityDecode(int iBit)
{
  if (iBit == 0)
  {
    m_iZero--;
  }
  else m_iOne--;
  m_iProbabilityOfOne = (m_iOne / (m_iZero + m_iOne)) * m_iL;
}

int TContextModeling::GetProbabilityOfOne()
{
  if (m_iProbabilityOfOne >= 0)
  {
    return 1;
  }
  else return m_iProbabilityOfOne;
}
