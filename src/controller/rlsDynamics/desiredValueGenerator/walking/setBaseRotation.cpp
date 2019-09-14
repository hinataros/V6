/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setBaseRotation(const Matrix3d &RB0)
{
  if(debug) DEBUG;

  RBw0 = RB0;
}
