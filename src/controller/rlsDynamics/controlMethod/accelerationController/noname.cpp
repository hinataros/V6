/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::noname(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // constraint
  VectorXd cal_dVcTildeRef = -cal_PcM.transpose()*cal_dVMRef;
  VectorXd hcth = cal_dPcM.transpose()*cal_VM + cal_dJcM*model.hoap2.all.dth;

  VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcTildeRef - hcth);

  // angular momentum
  MatrixXd HCBar = HC*N(cal_JcM);
  // VectorXd dlCDRef = -KDlC*model.hoap2.all.lC;
  VectorXd dlCthRef = dlCRef - IC*dwBRef;
  VectorXd dlCTildeRef = dlCthRef - HC*ddthcRef;

  VectorXd cmm = dIC*cal_VM.tail(3) + dHC*model.hoap2.all.dth;

  VectorXd ddthlCRef = N(cal_JcM)*pInv(HCBar)*(dlCTildeRef - cmm);

  // mobility
  if(info.contact.m.all){
    MatrixXd cal_JmMBar = cal_JmM*N(cal_JcM)*N(HCBar);
    VectorXd cal_dVmthRef = Bm.transpose()*cal_dVRef - cal_PmM.transpose()*cal_dVMRef;
    VectorXd cal_dVmTildeRef = cal_dVmthRef - cal_JmM*ddthlCRef;

    VectorXd hmth = -dBm.transpose()*cal_V + cal_dPmM.transpose()*cal_VM + cal_dJmM*model.hoap2.all.dth;

    VectorXd ddthmRef = N(cal_JcM)*N(HCBar)*pInv(cal_JmMBar)*(cal_dVmTildeRef - hmth);

    // redundancy
    VectorXd ddthnRef = N(cal_JcM)*N(HCBar)*N(cal_JmMBar)*ddthD(config, model);

    ddthRef = ddthcRef + ddthlCRef + ddthmRef + ddthnRef;

  }
  else{
    // redundancy
    // VectorXd ddthnRef = N(cal_JcM)*N(HCBar)*ddthD(config, model);
    VectorXd ddthnRef = N(cal_JcM)*ddthD(config, model);

    // ddthRef = ddthcRef + ddthlCRef + ddthnRef;
    ddthRef = ddthcRef + ddthnRef;
  }

  // // constraint
  // VectorXd cal_dVcthRef = -cal_PcM.transpose()*cal_dVMRef - cal_dPcM.transpose()*cal_VM;
  // VectorXd cal_Vcth = -cal_PcM.transpose()*cal_VM;

  // VectorXd ddthcRef = pInv(cal_JcM)*(cal_dVcthRef) + dpInv(cal_JcM, cal_dJcM)*cal_Vcth;

  // VectorXd ddthnRef = N(cal_JcM)*ddthD(config, model);

  // ddthRef = ddthcRef + ddthnRef;

  return ddqRef;
}
