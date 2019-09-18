/**
   @author Sho Miyahara 2017
*/

#ifndef INTERPOLATION_HPP_
#define INTERPOLATION_HPP_


#include "quaternion.hpp"

#include "spline3.hpp"
#include "spline5.hpp"

namespace RLS{
  class Interpolation:
    public Spline3, public Spline5{
  public:
    void unitQuaternionFix(Quaternion4d&, Quaternion4d&, Quaternion4d&); // amiyata
  };
}

#endif //INTERPOLATION_HPP_
