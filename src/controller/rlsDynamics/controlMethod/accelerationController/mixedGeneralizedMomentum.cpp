/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedGeneralizedMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(info.contact.c.all){
    MatrixXd JcM = MatrixXd::Zero(info.contact.c.all, info.dof.all);
    JcM <<
      cal_PcM.transpose(), cal_JcM;
    MatrixXd dJcM = MatrixXd::Zero(info.contact.c.all, info.dof.all);
    dJcM <<
      cal_dPcM.transpose(), cal_dJcM;

    MatrixXd ACBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
    ACBar <<
      cal_AM,
      JcM;

    MatrixXd dAC = MatrixXd::Zero(6, info.dof.all);
    dAC <<
      model.hoap2.all.dMM.block(0,0,6,info.dof.all);

    MatrixXd dACBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
    dACBar <<
      dAC,
      dJcM;

    VectorXd dqM = VectorXd::Zero(info.dof.all);
    dqM <<
      cal_VM,
      model.hoap2.all.dth;

    VectorXd cal_dLCBarRef = VectorXd::Zero(6+info.contact.c.all);
    cal_dLCBarRef.head(6) = cal_dLCRef;

    VectorXd ddqLCRef = pInv(ACBar)*(cal_dLCBarRef - dACBar*dqM);

    if(info.contact.m.all){
      // **********************************************************
      MatrixXd JmM = MatrixXd::Zero(info.contact.m.all, info.dof.all);
      JmM <<
        cal_PmM.transpose(), cal_JmM;
      MatrixXd dJmM = MatrixXd::Zero(info.contact.m.all, info.dof.all);
      dJmM <<
        cal_dPmM.transpose(), cal_dJmM;

      MatrixXd JmMBar = JmM*N(ACBar);

      VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
      VectorXd dVmTildeRef = dVmBarRef - dJmM*dqM - JmM*ddqLCRef;

      VectorXd ddqmRef = N(ACBar)*pInv(JmMBar)*dVmTildeRef;

      ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqD(config, info, model);
    }
    else{
      ddqMoptRef = ddqLCRef + N(ACBar)*ddqD(config, info, model);
    }
  }
  // ddqMoptRef = VectorXd::Zero(info.dof.all);

  return ddqMoptRef;
}
