#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::cl_Bacc(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // constraint
  VectorXd cal_dVcBarRef = -cal_Pc.transpose()*cal_dVBRef;

  VectorXd ddthcRef = pInv(cal_Jc)*cal_dVcBarRef;

  // mobility
  MatrixXd cal_JmBar = cal_Jm*N(cal_Jc);
  VectorXd cal_dVmBarRef = Bm.transpose()*cal_dVRef - cal_Pm.transpose()*cal_dVBRef;
  VectorXd cal_dVmTildeRef = cal_dVmBarRef - cal_Jm*pInv(cal_Jc)*cal_dVcBarRef;

  VectorXd ddthmRef = pInv(cal_JmBar)*cal_dVmTildeRef;

  // nonlinear
  VectorXd hc = cal_dPc.transpose()*cal_VB + cal_dJc*model.hoap2.all.dth;
  VectorXd hm = -dBm.transpose()*cal_V + cal_dPm.transpose()*cal_VB + cal_dJm*model.hoap2.all.dth;

  VectorXd h = pInv(cal_Jc)*hc + pInv(cal_JmBar)*(hm - cal_Jm*pInv(cal_Jc)*hc);

  ddthRef = ddthcRef + ddthmRef - h;

  ddqRef <<
    cal_dVBRef,
    ddthRef;

  return ddqRef;
}
