/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::highGainController()
{
  if(debug) DEBUG;

  (this->*motionController_ptr)();

  thDes += dthRef*worldModel->dt;

  tau = KdHG*(dthRef - model->dth) + KpHG*(thDes - model->th);

  return tau;
}
