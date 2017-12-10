#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <stdarg.h>

namespace RLS{
  class Common{
  private:
  protected:
    double math(string, int, ...);
    MatrixXd diag(int, ...);
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

    Vector3d R2xi(Matrix3d);
    Matrix3d xi2R(Vector3d);
    Vector3d dxi2w(Vector3d, Vector3d);
    Vector3d w2dxi(Vector3d, Vector3d);
    Vector3d ddxi2dw(Vector3d, Vector3d, Vector3d);

  public:
  };
}

#endif // COMMON_HPP_
