/**
   @author Sho Miyahara 2017
*/

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <stdarg.h>

namespace RLS{
  class Common{
  private:
  protected:
    double math(string, int, ...);
    MatrixXd diag(int, ...);
    MatrixXd antiDiag(int, ...);
    Matrix3d R(string, double);
    Matrix3d cross(Vector3d);
    Matrix6d bb_R(string, double);
    Matrix6d bb_T(Vector3d);

    MatrixXd B(int, ...);

    MatrixXd pInv(MatrixXd);
    MatrixXd pInv(MatrixXd, MatrixXd);
    MatrixXd N(MatrixXd);
    MatrixXd N(MatrixXd, MatrixXd);
    MatrixXd Nast(MatrixXd);
    MatrixXd Nast(MatrixXd, MatrixXd);

    MatrixXd dpInv(MatrixXd, MatrixXd);
    MatrixXd dN(MatrixXd, MatrixXd);

    Matrix3d inverse3d(Matrix3d); // amiyata

    Vector3d R2xi(Matrix3d);
    Matrix3d xi2R(Vector3d);
    Vector3d dxi2w(Vector3d, Vector3d);
    Vector3d w2dxi(Vector3d, Vector3d);
    Matrix3d w2dR(Vector3d, Matrix3d);
    Vector3d ddxi2dw(Vector3d, Vector3d, Vector3d);

    VectorXd arrayd2Vector(int, double*); // amiyata
    double sign(double); // amiyata

    int round_cast(double, int);

    bool nanCheck(VectorXd);

  public:
  };
}

#endif // COMMON_HPP_
