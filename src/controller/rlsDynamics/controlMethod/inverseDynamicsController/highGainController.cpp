/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::highGainController()
{
  if(debug) DEBUG;

  if(!extMotionController)
    (this->*motionController_ptr)();
  else
    (ext->*ext_motionController_ptr)(this);

  thDes += dthRef*worldModel->dt;

  tau = KdHG*(dthRef - model->dth) + KpHG*(thDes - model->th);

  return tau;
}
