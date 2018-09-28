/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

Vector2d RLS::RlsDynamics::F2rp(const Vector6d &cal_F)
{
  if(cal_F(2)==0.)
    return Vector2d::Zero();

  return (1/cal_F(2))*(-cal_Sp)*cal_F;
}
