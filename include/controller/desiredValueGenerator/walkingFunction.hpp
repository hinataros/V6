// amiyata
#ifndef WALKING_FUNCTION_HPP
#define WALKING_FUNCTION_HPP

namespace RLS{
  class WalkingFunction{
  private:

  public:
    double intPow(double, int);
    double factorio(int, int);

    MatrixXd makeCMat(int, double);

    MatrixXd makePosBoundary(int, double, double);
    MatrixXd makePosBoundary(int, VectorXd, VectorXd);

    MatrixXd findPolyParam(double, double tf, MatrixXd);
    MatrixXd findPolyParam(double, double, MatrixXd, MatrixXd);

    MatrixXd maketMat(int, int, double);
    MatrixXd maketMat(int, double);

    MatrixXd finddPolyParam(double, double, MatrixXd);
    MatrixXd makedtMat(int, int, double);
    MatrixXd makedtMat(int, double);
  };
}

#endif
