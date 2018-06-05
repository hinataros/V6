/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedAccelerationSynergy(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // constraint
  VectorXd cal_dVcMBarRef = -cal_PcM.transpose()*cal_dVMRef;

  VectorXd ddthcRef = pInv(cal_JcM)*cal_dVcMBarRef;

  // mobility
  MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM);
  VectorXd cal_dVmMBarRef = Bm.transpose()*cal_dVRef - cal_PmM.transpose()*cal_dVMRef;
  VectorXd cal_dVmMTildeRef = cal_dVmMBarRef - cal_JmM*pInv(cal_JcM)*cal_dVcMBarRef;

  VectorXd ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef;

  // nonlinear
  VectorXd hcM = cal_dPcM.transpose()*cal_VM + cal_dJcM*model.hoap2.all.dth;
  VectorXd hmM = -dBm.transpose()*cal_V + cal_dPmM.transpose()*cal_VM + cal_dJmM*model.hoap2.all.dth;

  VectorXd h = pInv(cal_JcM)*hcM + pInv(cal_JmMBar)*(hmM - cal_JmM*pInv(cal_JcM)*hcM);

  ddthRef = ddthcRef + ddthmRef - h;

  ddqMRef <<
    cal_dVMRef,
    ddthRef;

  return ddqMRef;
}
