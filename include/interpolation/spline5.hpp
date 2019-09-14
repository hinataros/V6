/**
   @author Sho Miyahara 2017
*/

#include "common.hpp"

namespace RLS{
  class Spline5:
    virtual public Common{
  private:
    Vector3d par;
    Vector6d a;
  public:
    Vector3d makeSpline5(double, double, double, double);
    Vector3d makeSpline5(double, double, double, double, double, double, double, double);

    Matrix3d makeSpline5(double, double, Vector3d, Vector3d);
  };
}
