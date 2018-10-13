/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::hogehogeMomentum()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  int qwdof = 3 + info.model.dof.joint;

  VectorXd dqw = model->dqM.tail(qwdof);

  VectorXd ddq1Ref = VectorXd::Zero(qwdof);
  MatrixXd Jcw = MatrixXd::Zero(info.constraint.c.all, qwdof);
  if(info.constraint.c.all){
    MatrixXd Ccf = cal_PcM.block(0,0,3,info.constraint.c.all);
    MatrixXd Ccm = cal_PcM.block(3,0,3,info.constraint.c.all);
    MatrixXd dCcm = cal_dPcM.block(3,0,3,info.constraint.c.all);

    Jcw <<
      Ccm.transpose(), cal_JcM;
    MatrixXd dJcw = MatrixXd::Zero(info.constraint.c.all, qwdof);
    dJcw <<
      dCcm.transpose(), cal_dJcM;

    VectorXd cal_dVccRef = -Ccf.transpose()*(dpRef/model->M) - dJcw*dqw;

    ddq1Ref = pInv(Jcw)*cal_dVccRef;
  }

  MatrixXd Jmw = MatrixXd::Zero(info.constraint.m.all, qwdof);
  MatrixXd JmwBar = MatrixXd::Zero(info.constraint.m.all, qwdof);
  MatrixXd dJmw = MatrixXd::Zero(info.constraint.m.all, qwdof);
  MatrixXd Cmf = cal_PmM.block(0,0,3,info.constraint.m.all);
  MatrixXd Cmm = cal_PmM.block(3,0,3,info.constraint.m.all);
  MatrixXd dCmm = cal_dPmM.block(3,0,3,info.constraint.m.all);

  // ****************************************************************
  VectorXd ddq2Ref = VectorXd::Zero(qwdof);
  if(info.constraint.m.all){
    Jmw <<
      Cmm.transpose(), cal_JmM;
    dJmw <<
      dCmm.transpose(), cal_dJmM;
  }

  JmwBar = Jmw*N(Jcw);

  VectorXd dVmBarRef = cal_dVmBarRef + dBm.transpose()*model->cal_V;
  VectorXd cal_dVmcRef = dVmBarRef - Cmf.transpose()*(dpRef/model->M) - dJmw*dqw;
  ddq2Ref = N(Jcw)*pInv(JmwBar)*cal_dVmcRef;

  VectorXd ddq3Ref = VectorXd::Zero(qwdof);
  MatrixXd Aw = MatrixXd::Zero(3, qwdof);
  Aw <<
    model->IC, model->HC;

  MatrixXd AwBar = MatrixXd::Zero(3, qwdof);
  AwBar = Aw*N(Jcw)*N(JmwBar);

  VectorXd dlCcRef = dlCRef - model->cmm;

  ddq3Ref = N(Jcw)*N(JmwBar)*pInv(AwBar)*dlCcRef;

  VectorXd ddqnRef = N(Jcw)*N(JmwBar)*N(AwBar)*ddqthinit().tail(qwdof);
  // // ****************************************************************

  // VectorXd ddq2Ref = VectorXd::Zero(qwdof);
  // MatrixXd Aw = MatrixXd::Zero(3, qwdof);
  // Aw <<
  //   model->IC, model->HC;

  // MatrixXd AwBar = MatrixXd::Zero(3, qwdof);
  // AwBar = Aw*N(Jcw);

  // VectorXd dlCcRef = dlCRef - model->cmm;

  // ddq2Ref = N(Jcw)*pInv(AwBar)*dlCcRef;

  // VectorXd ddq3Ref = VectorXd::Zero(qwdof);
  // if(info.constraint.m.all){
  //   Jmw <<
  //     Cmm.transpose(), cal_JmM;
  //   dJmw <<
  //     dCmm.transpose(), cal_dJmM;
  // }

  // JmwBar = Jmw*N(Jcw)*N(AwBar);

  // VectorXd dVmBarRef = cal_dVmBarRef + dBm.transpose()*model->cal_V;
  // VectorXd cal_dVmcRef = dVmBarRef - Cmf.transpose()*(dpRef/model->M) - dJmw*dqw;
  // ddq3Ref = N(Jcw)*N(AwBar)*pInv(JmwBar)*cal_dVmcRef;

  // VectorXd ddqnRef = N(Jcw)*N(AwBar)*N(JmwBar)*ddqthinit().tail(qwdof);
  // // ****************************************************************

  ddqwoptRef = ddq1Ref + ddq2Ref + ddq3Ref + ddqnRef;

  return ddqwoptRef;
}
