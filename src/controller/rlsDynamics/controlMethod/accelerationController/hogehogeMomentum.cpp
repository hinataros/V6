/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::hogehogeMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  int qwdof = 3 + info.dof.joint;

  VectorXd dqw = dqM.tail(qwdof);

  VectorXd ddq1Ref = VectorXd::Zero(qwdof);
  MatrixXd Jcw = MatrixXd::Zero(info.contact.c.all, qwdof);
  if(info.contact.c.all){
    MatrixXd Ccf = cal_PcM.block(0,0,3,info.contact.c.all);
    MatrixXd Ccm = cal_PcM.block(3,0,3,info.contact.c.all);
    MatrixXd dCcm = cal_dPcM.block(3,0,3,info.contact.c.all);

    Jcw <<
      Ccm.transpose(), cal_JcM;
    MatrixXd dJcw = MatrixXd::Zero(info.contact.c.all, qwdof);
    dJcw <<
      dCcm.transpose(), cal_dJcM;

    VectorXd cal_dVccRef = -Ccf.transpose()*(dpRef/model.hoap2.all.m) - dJcw*dqw;

    ddq1Ref = pInv(Jcw)*cal_dVccRef;
  }

  MatrixXd Jmw = MatrixXd::Zero(info.contact.m.all, qwdof);
  MatrixXd JmwBar = MatrixXd::Zero(info.contact.m.all, qwdof);
  MatrixXd dJmw = MatrixXd::Zero(info.contact.m.all, qwdof);
  MatrixXd Cmf = cal_PmM.block(0,0,3,info.contact.m.all);
  MatrixXd Cmm = cal_PmM.block(3,0,3,info.contact.m.all);
  MatrixXd dCmm = cal_dPmM.block(3,0,3,info.contact.m.all);

  // ****************************************************************
  VectorXd ddq2Ref = VectorXd::Zero(qwdof);
  if(info.contact.m.all){
    Jmw <<
      Cmm.transpose(), cal_JmM;
    dJmw <<
      dCmm.transpose(), cal_dJmM;
  }

  JmwBar = Jmw*N(Jcw);

  VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
  VectorXd cal_dVmcRef = dVmBarRef - Cmf.transpose()*(dpRef/model.hoap2.all.m) - dJmw*dqw;
  ddq2Ref = N(Jcw)*pInv(JmwBar)*cal_dVmcRef;

  VectorXd ddq3Ref = VectorXd::Zero(qwdof);
  MatrixXd Aw = MatrixXd::Zero(3, qwdof);
  Aw <<
    IC, HC;

  MatrixXd AwBar = MatrixXd::Zero(3, qwdof);
  AwBar = Aw*N(Jcw)*N(JmwBar);

  VectorXd dlCcRef = dlCRef - cal_CM.tail(3);

  ddq3Ref = N(Jcw)*N(JmwBar)*pInv(AwBar)*dlCcRef;

  VectorXd ddqnRef = N(Jcw)*N(JmwBar)*N(AwBar)*ddqthinit(config, info, model).tail(qwdof);
  // // ****************************************************************

  // VectorXd ddq2Ref = VectorXd::Zero(qwdof);
  // MatrixXd Aw = MatrixXd::Zero(3, qwdof);
  // Aw <<
  //   IC, HC;

  // MatrixXd AwBar = MatrixXd::Zero(3, qwdof);
  // AwBar = Aw*N(Jcw);

  // VectorXd dlCcRef = dlCRef - cal_CM.tail(3);

  // ddq2Ref = N(Jcw)*pInv(AwBar)*dlCcRef;

  // VectorXd ddq3Ref = VectorXd::Zero(qwdof);
  // if(info.contact.m.all){
  //   Jmw <<
  //     Cmm.transpose(), cal_JmM;
  //   dJmw <<
  //     dCmm.transpose(), cal_dJmM;
  // }

  // JmwBar = Jmw*N(Jcw)*N(AwBar);

  // VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
  // VectorXd cal_dVmcRef = dVmBarRef - Cmf.transpose()*(dpRef/model.hoap2.all.m) - dJmw*dqw;
  // ddq3Ref = N(Jcw)*N(AwBar)*pInv(JmwBar)*cal_dVmcRef;

  // VectorXd ddqnRef = N(Jcw)*N(AwBar)*N(JmwBar)*ddqthinit(config, info, model).tail(qwdof);
  // // ****************************************************************

  ddqwoptRef = ddq1Ref + ddq2Ref + ddq3Ref + ddqnRef;

  return ddqwoptRef;
}
