/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::highGainController(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  (this->*motionController_ptr)(info);

  thDes += dthRef*dt;

  tau = KdHG*(dthRef - dth) + KpHG*(thDes - th);

  return tau;
}
