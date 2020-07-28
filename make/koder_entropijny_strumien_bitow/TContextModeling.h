
class TContextModeling
{
private:
  int m_iProbabilityOfOne;
  int m_iL;
  double m_iOne;
  double m_iZero;
public:
  TContextModeling(int iL);
  double GetOne();
  double GetZero();
  void SetProbabilityOfOne(int ProbOne);
  void SetOne(double One);
  void SetZero(double Zero);
  void SaveProbability(int iProbabilityOfOne, int iOne, int iZero);
  void ChangeProbabilityCode(int iBit);
  void ChangeProbabilityDecode(int iBit);
  int GetProbabilityOfOne();

};
