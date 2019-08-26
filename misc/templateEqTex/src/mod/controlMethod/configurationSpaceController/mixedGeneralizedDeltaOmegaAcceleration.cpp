/**
   @author Akinori Miyata 2019
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedGeneralizedDeltaOmegaAcceleration()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  MatrixXd BwCIC = (BwC.transpose()*model->IC).transpose();
  MatrixXd BwCICExc = (BwCAut.transpose()*model->IC).transpose();
  // MatrixXd BwCIC = (BwC.transpose()).transpose();
  // MatrixXd BwCICExc = (BwCAut.transpose()).transpose();

  // Vector3d Deltaw = wC - model->wB;

  // Vector3d dwC = model->IC.inverse() * (cal_dLCRef.segment(3,3) - model->dIC*wC);
  Vector3d dwC = -KDlC * model->wC;
  // Vector3d dwC = -KDlC * wC - model->IC.inverse()*model->dIC*wC;
  Vector3d dDeltaw = dwC - fb.dwBfb;
  // Vector3d dDeltaw = - KDlC * Deltaw;

  int m=info.constraint->m.all, c=info.constraint->c.all;
  int j=info.model.dof.joint, a=info.model.dof.all;

  MatrixXd TM = MatrixXd::Zero(6+wCcD, a);
  TM <<
    MatrixXd::Identity(6,6), MatrixXd::Zero(6,j),
    MatrixXd::Zero(wCcD,3), BwCIC.transpose(), BwCIC.transpose()*model->Jw; //dwC
    // MatrixXd::Zero(wCcD,3), MatrixXd::Zero(wCcD,3), BwCIC.transpose()*model->Jw; //dDeltaw

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
    MatrixXd::Zero(wCcD,6), BwCIC.transpose()*model->dJw;

  VectorXd dVMRef = VectorXd::Zero(6+wCcD);
  dVMRef <<
    fb.cal_dVMfb,
    BwCIC.transpose()*dwC;
    // BwCIC.transpose()*dDeltaw;
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
    MatrixXd::Zero(3,3), BwC;
  SLExc <<
    MatrixXd::Zero(3,3-wCcD),
    BwCAut;

  /////////////////////////////momentum ver.
  MatrixXd AMBar = MatrixXd::Zero(6+wCcD+m+c, a);
  MatrixXd bb = MatrixXd::Zero(3, a);
  bb.block(0,3, 3,3) = MatrixXd::Identity(3,3);
  AMBar <<
    model->cal_AM.block(0,0, 3,a),
    bb,
    BwCIC.transpose() * model->cal_AM.block(3,0, 3,a),
    constraintModel.JmM,
    constraintModel.JcM;

  VectorXd VMBar = VectorXd::Zero(6+wCcD+m+c);
  VMBar <<
    cal_dLCRef.segment(0,3),
    fb.dwBfb,
    BwCIC.transpose()*cal_dLCRef.segment(3,3),
    cal_dVmBarRef,
    VectorXd::Zero(c);

  MatrixXd dAMBar = MatrixXd::Zero(6+wCcD+m+c, a);
  dAMBar <<
    model->cal_dAM.block(0,0, 3,a),
    MatrixXd::Zero(3, a),
    BwCIC.transpose()*model->cal_dAM.block(3,0, 3,a),
    constraintModel.dJmM,
    constraintModel.dJcM;
//////////////////////////////

  MatrixXd Weight = MatrixXd::Zero(6+wCcD+m+c, 6+wCcD+m+c);
  Weight <<
    model->M*MatrixXd::Identity(3,3), MatrixXd::Zero(3,3+wCcD+m+c),
    MatrixXd::Zero(3,3), MatrixXd::Identity(3,3), MatrixXd::Zero(3,wCcD+m+c),
    MatrixXd::Zero(wCcD,6), BwCIC.transpose()*model->IC*BwC, MatrixXd::Zero(wCcD, m+c),
    MatrixXd::Zero(m+c,6+wCcD), MatrixXd::Identity(m+c, m+c);

  // o(( (Weight*AM) - (AMBar) ));
  // o((Weight*(AMRef - dAM * model->dqM)) - (VMBar - dAMBar*model->dqM));
  // o(model->IC*);
  // gc;
  // MatrixXd Weight_q = AM.transpose() * Weight * AM;

  ddqMoptRef = pInv(Weight*AM) * Weight*(AMRef - dAM * model->dqM) + N(Weight*AM) * ddqthD();
  // ddqMoptRef = pInv(AM) * (AMRef - dAM * model->dqM);
  // ddqMoptRef = pInv(AM, Weight_q) * (AMRef - dAM * model->dqM) + N(AM) * ddqthD();

  ddthRef = ddqMoptRef.segment(6, j);

  VectorXd cal_dLCBarOpt = model->cal_AM*ddqMoptRef + model->cal_dAM*model->dqM;
  VectorXd cal_dLCBarwC  = VectorXd::Zero(6);
  cal_dLCBarwC <<
    model->M * fb.dvCfb,
    model->IC * dwC + model->dIC * model->wC;
    // model->IC * dwC;
  cal_dLCRef = SL*SL.transpose()*cal_dLCBarwC + SLExc*SLExc.transpose()*cal_dLCBarOpt;

  // cal_dLCRef = cal_dLCBarOpt;

  return ddqMoptRef;
}
