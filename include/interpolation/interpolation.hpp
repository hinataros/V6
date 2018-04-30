/**
   @author Sho Miyahara 2017
*/

#ifndef INTERPOLATION_HPP_
#define INTERPOLATION_HPP_

#include "spline3.hpp"
#include "spline5.hpp"

namespace RLS{
  class Interpolation:
    public Spline3, public Spline5{
  public:
  };
}

#endif //INTERPOLATION_HPP_
