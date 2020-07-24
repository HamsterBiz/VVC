
class TContextModeling
{
private:
  int m_iProbabilityOfOne;
  int m_iL;
  double m_iOne;
  double m_iZero;
public:
  TContextModeling(int iL);
  void SaveProbability(int iProbabilityOfOne, int iOne, int iZero);

  void ChangeProbabilityCode(int iBit);
  void ChangeProbabilityDecode(int iBit);
  int GetProbabilityOfOne();

};
