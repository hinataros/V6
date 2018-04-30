/**
   @author Sho Miyahara 2017
*/

#include "common.hpp"

namespace RLS{
  class Spline3:
    virtual public Common{
  private:
    Vector3d par;
    Vector6d a;
  public:
    Vector3d makeSpline3(double, double, double, double);
    Vector3d makeSpline3(double, double, double, double, double, double);
  };
}
