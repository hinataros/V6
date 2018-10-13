/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::workAcceleration()
{
  if(debug) DEBUG;

  // mobility
  ddthRef = pInv(cal_Jm)*(cal_dVmBarRef - cal_dJm*model->dth);

  ddqBRef <<
    fb.cal_dVBfb,
    ddthRef;

  return ddqBRef;
}
