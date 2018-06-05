/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::workAcceleration(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // mobility
  VectorXd cal_dVmRef = Bm.transpose()*cal_dVRef;

  ddthRef = pInv(cal_Jm)*(cal_dVmRef - cal_dJm*model.hoap2.all.dth);

  ddqBRef <<
    cal_dVBRef,
    ddthRef;

  return ddqBRef;
}
