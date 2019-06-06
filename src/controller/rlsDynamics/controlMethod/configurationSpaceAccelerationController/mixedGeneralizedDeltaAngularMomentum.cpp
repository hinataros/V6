/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedGeneralizedDeltaAngularMomentum()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  Vector3d dwCRef = - KDlC * model->wC;
  Vector3d dDeltaw = dwCRef - fb.dwBfb;

  VectorXd dDeltalRef = model->IC * dDeltaw;

  int m=info.constraint->m.all, c=info.constraint->c.all;
  int j=info.model.dof.joint, a=info.model.dof.all;

  MatrixXd TM = MatrixXd::Zero(6+lCcD, a);
  TM <<
    MatrixXd::Identity(6,6), MatrixXd::Zero(6,j),
    MatrixXd::Zero(lCcD,3), MatrixXd::Zero(lCcD,3), BLC.block(3,pcD, 3,lCcD).transpose()*model->HC;

  MatrixXd JP = MatrixXd::Zero(m+c, a);
  JP <<
    constraintModel.JmM,
    constraintModel.JcM;
  MatrixXd dJP = MatrixXd::Zero(m+c, a);
  dJP <<
    constraintModel.dJmM,
    constraintModel.dJcM;
  MatrixXd NM = MatrixXd::Zero(6+lCcD, a);
  NM <<
    MatrixXd::Zero(6, a),
    MatrixXd::Zero(lCcD,6), BLC.block(3,pcD, 3,lCcD).transpose()*model->dHC;

  VectorXd dVMRef = VectorXd::Zero(6+lCcD);
  dVMRef <<
    fb.cal_dVMfb,
    BLC.block(3,pcD, 3,lCcD).transpose() * dDeltalRef;
  VectorXd dVPRef = VectorXd::Zero(m+c);
  dVPRef <<
    cal_dVmBarRef,
    VectorXd::Zero(c);

  VectorXd AMRef = VectorXd::Zero(6+lCcD+m+c);
  AMRef <<
    dVMRef,
    dVPRef;

  MatrixXd AM = MatrixXd::Zero(6+lCcD+m+c, a);
  AM <<
    TM,
    JP;
  MatrixXd dAM = MatrixXd::Zero(6+lCcD+m+c, a);
  dAM <<
    NM,
    dJP;

  // ddqMoptRef = pInv(AM) * (AMRef - dAM * model->dqM) + N(AM) * ddqthD();
  ddqMoptRef = pInv(AM) * (AMRef - dAM * model->dqM) + N(AM) * ddqthinit();
  ddthRef = ddqMoptRef.segment(6, j);

  VectorXd cal_dLCBarOpt = model->cal_AM*ddqMoptRef + model->cal_dAM*model->dqM;
  VectorXd cal_dLCBarwC  = VectorXd::Zero(6);
  cal_dLCBarwC <<
    model->M * fb.dvCfb,
    model->IC * dwCRef + model->dIC * model->wC;
  cal_dLCRef = BLC*BLC.transpose()*cal_dLCBarwC + BLCAut*BLCAut.transpose()*cal_dLCBarOpt;


  return ddqMoptRef;
}
