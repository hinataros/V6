#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cl_Mcoord(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  VectorXd cal_dVcMBarRef = VectorXd::Zero(c);
  cal_dVcMBarRef = -cal_PcM.transpose()*cal_dVMRef;

  ddthcRef = pInv(cal_JcM)*cal_dVcMBarRef;

  VectorXd cal_dVmMBarRef = VectorXd::Zero(m);
  cal_dVmMBarRef = Bm.transpose()*cal_dVRef - cal_PmM.transpose()*cal_dVMRef;
  VectorXd cal_dVmMTildeRef = VectorXd::Zero(m);
  cal_dVmMTildeRef = cal_dVmMBarRef - cal_JmM*pInv(cal_JcM)*cal_dVcMBarRef;
  MatrixXd cal_JmMBar = MatrixXd::Zero(m, info.dof.joint);
  cal_JmMBar = cal_JmM*N(cal_JcM);

  ddthmRef = pInv(cal_JmMBar)*cal_dVmMTildeRef;

  VectorXd hcM = VectorXd::Zero(info.dof.joint);
  hcM = cal_dPcM.transpose()*cal_VM + cal_dJcM*model.all.dth;
  VectorXd hmM = VectorXd::Zero(info.dof.joint);
  hmM = -dBm.transpose()*cal_V + cal_dPmM.transpose()*cal_VM + cal_dJmM*model.all.dth;

  h = pInv(cal_JcM)*hcM + pInv(cal_JmMBar)*(hmM - cal_JmM*pInv(cal_JcM)*hcM);

  ddthRef = ddthcRef + ddthmRef - h;
}
