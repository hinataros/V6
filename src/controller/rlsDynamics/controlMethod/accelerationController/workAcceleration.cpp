/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::workAcceleration(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // mobility
  VectorXd cal_dVmRef = Bm.transpose()*cal_dVRef;

  ddthRef = pInv(cal_Jm)*(cal_dVmRef - cal_dJm*dth);

  ddqBRef <<
    cal_dVBRef,
    ddthRef;

  return ddqBRef;
}
