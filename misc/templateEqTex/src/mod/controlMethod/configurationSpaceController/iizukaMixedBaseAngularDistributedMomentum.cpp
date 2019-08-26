/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedBaseAngularDistributedMomentum()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  int wCcD = info.constraint->wC;
  Vector3d dwCRef = - KDlC * wC;

  double KDthHl = 50;
  VectorXd ddtharm = VectorXd::Zero(info.model.dof.joint);
  ddtharm.segment(6*2+1,7) = -KDthHl*model->dth.segment(6*2+1,7);
  // ddtharm = -KDth*model->dth;
  // o(-KDth*model->dth);
  // o(ddtharm);
  fb.dwBfb = -KDlC*wC - model->Jw*ddtharm - model->dJw*model->dth;
  // fb.dwBfb = ((-KDlC*wC)*1/5) - model->Jw*ddtharm - model->dJw*model->dth;
  // fb.dwBfb = -KDlC*wC*(8/10);
  fb.cal_dVMfb <<
    fb.dvCfb,
    fb.dwBfb;

  Vector3d dDeltaw = dwCRef - fb.dwBfb;

  VectorXd dDeltalRef = model->IC * dDeltaw;

  int m=info.constraint->m.all, c=info.constraint->c.all;
  int j=info.model.dof.joint, a=info.model.dof.all;

  MatrixXd TM = MatrixXd::Zero(6+wCcD, a);
  TM <<
    MatrixXd::Identity(6,6), MatrixXd::Zero(6,j),
    MatrixXd::Zero(wCcD,3), MatrixXd::Zero(wCcD,3), CwC.transpose()*model->HC;

  MatrixXd JP = MatrixXd::Zero(m+c, a);
  JP <<
    constraintModel.JmM,
    constraintModel.JcM;
  MatrixXd dJP = MatrixXd::Zero(m+c, a);
  dJP <<
    constraintModel.dJmM,
    constraintModel.dJcM;
  MatrixXd NM = MatrixXd::Zero(6+wCcD, a);
  NM <<
    MatrixXd::Zero(6, a),
    MatrixXd::Zero(wCcD,6), CwC.transpose()*model->dHC;

  VectorXd dVMRef = VectorXd::Zero(6+wCcD);
  dVMRef <<
    fb.cal_dVMfb,
    CwC.transpose() * dDeltalRef;
  VectorXd dVPRef = VectorXd::Zero(m+c);
  dVPRef <<
    cal_dVmBarRef,
    VectorXd::Zero(c);

  VectorXd AMRef = VectorXd::Zero(6+wCcD+m+c);
  AMRef <<
    dVMRef,
    dVPRef;

  MatrixXd AM = MatrixXd::Zero(6+wCcD+m+c, a);
  AM <<
    TM,
    JP;
  MatrixXd dAM = MatrixXd::Zero(6+wCcD+m+c, a);
  dAM <<
    NM,
    dJP;

  MatrixXd SL = MatrixXd::Zero(3+3, 3+wCcD);
  MatrixXd SLExc = MatrixXd::Zero(3+3, (3-wCcD));
  SL <<
    BLC.block(0,0, 3,3), MatrixXd::Zero(3, wCcD),
    MatrixXd::Zero(3,3), CwC;
  SLExc <<
    MatrixXd::Zero(3,3-wCcD),
    CwCExc;

  ddqMoptRef = pInv(AM) * (AMRef - dAM * model->dqM) + N(AM) * ddqthD();
  ddthRef = ddqMoptRef.segment(6, j);

  VectorXd cal_dLCBarOpt = model->cal_AM*ddqMoptRef + model->cal_dAM*model->dqM;
  VectorXd cal_dLCBarwC  = VectorXd::Zero(6);
  cal_dLCBarwC <<
    model->M * fb.dvCfb,
    model->IC * dwCRef + model->dIC * wC;
  cal_dLCRef = SL*SL.transpose()*cal_dLCBarwC + SLExc*SLExc.transpose()*cal_dLCBarOpt;


  return ddqMoptRef;
}
