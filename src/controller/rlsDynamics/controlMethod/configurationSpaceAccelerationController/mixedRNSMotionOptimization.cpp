/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedRNSMotionOptimization()
{
  if(debug) DEBUG;

  (this->*operationalSpaceController_ptr)();

  int constraint_num =
    6 + wCcD + info.constraint->c.all + info.constraint->m.all;
    // info.constraint->wB + info.constraint->mcal_LC + info.constraint->c.all + info.constraint->m.all;
  int AMnum =
    6 + wCcD;

  MatrixXd LwB = MatrixXd::Zero(3, info.model.dof.all); // iizuka: ddqMからwB成分を抜き出す行列
  LwB << Matrix3d::Zero(),Matrix3d::Identity(),MatrixXd::Zero(3,info.model.dof.joint);

  MatrixXd Jw = MatrixXd::Zero(3,info.model.dof.joint);
  MatrixXd dJw = MatrixXd::Zero(3,info.model.dof.joint);
  Jw = model->IC.inverse() * model->HC;
  dJw = model->IC*model->dHC - model->IC.inverse()*model->dIC*model->IC.inverse()*model->HC; // d(IC^-1)/dt = - IC^-1 * dIC * IC^-1

  MatrixXd LDw = MatrixXd::Zero(3, info.model.dof.all); // iizuka: ddqMからwB成分を抜き出す行列
  MatrixXd LdDw = MatrixXd::Zero(3, info.model.dof.all); // iizuka: ddqMからwB成分を抜き出す行列
  LDw << Matrix3d::Zero(),Matrix3d::Zero(), Jw;
  LdDw << Matrix3d::Zero(),Matrix3d::Zero(), dJw;

  MatrixXd mcTM = MatrixXd::Zero(AMnum,info.model.dof.joint+6);
  mcTM <<
    Matrix3d::Identity(), Matrix3d::Zero(), MatrixXd::Zero(3, info.model.dof.joint),
    Matrix3d::Zero(), Matrix3d::Identity(),MatrixXd::Zero(3,info.model.dof.joint),
    BwC.transpose()*LDw;

  MatrixXd dmcTM = MatrixXd::Zero(AMnum,info.model.dof.joint+6);
  dmcTM.block(6, 0, wCcD, info.model.dof.all) = BwC.transpose()*LdDw;
  Vector3d vCRef = model->wX*(fb.drXfb - model->vC);
  Vector3d Ddw = Vector3d::Zero();
  Vector3d wC = Vector3d::Zero();
  Vector3d dwCRef = Vector3d::Zero();
  Vector3d dlCREF = Vector3d::Zero();
  wC = model->wB+Jw*model->dth;
  dlCREF = -KDlC*(model->IC*model->wB+model->HC*model->dth);
  dwCRef = model->IC.inverse()*(dlCREF-model->dIC*wC);
  // dwCRef = -1000*wC;
  Ddw = dwCRef - fb.dwBfb;

  cal_dLCRef.tail(3) = Ddw;

  VectorXd dmcAMRef = VectorXd::Zero(AMnum);
  dmcAMRef <<
    vCRef,
    fb.dwBfb,
    BwC.transpose()*Ddw;

  // model->cal_AM.block(3,0,3,info.model.dof.all) << LJw;
  // MatrixXd calAM = MatrixXd::Zero(6, info.model.dof.all);
  // calAM << model->cal_AM.block(0,0,3,info.model.dof.all), LJw;
  // MatrixXd caldAM = MatrixXd::Zero(6, info.model.dof.all);
  // caldAM << model->cal_dAM.block(0,0,3,info.model.dof.all), LdJw;

  MatrixXd ACBar = MatrixXd::Zero(constraint_num, info.model.dof.joint+6);
  // ACBar <<
  //   constraintModel.BwC.transpose()*LwB,
  //   constraintModel.JcM,
  //   constraintModel.JmM,
  //   BLC.transpose()*model->cal_AM;
  ACBar <<
    mcTM,
    constraintModel.JcM,
    constraintModel.JmM;
    // constraintModel.BwC.transpose()*LwB,
    // constraintModel.JcM,
    // constraintModel.JmM,
    // BLC.transpose()*calAM;
  MatrixXd dACBar = MatrixXd::Zero(constraint_num, info.model.dof.all);

  dACBar <<
    dmcTM,
    constraintModel.dJcM,
    constraintModel.dJmM;

  // dACBar <<
  //   MatrixXd::Zero(info.constraint->wB,info.model.dof.all),
  //   constraintModel.dJcM,
  //   constraintModel.dJmM,
  //   BLC.transpose()*caldAM;



  MatrixXd cal_dLCBarRef = VectorXd::Zero(constraint_num);
  cal_dLCBarRef <<
    dmcAMRef,
    VectorXd::Zero(info.constraint->c.all),
    cal_dVmBarRef + constraintModel.dBm.transpose()*model->cal_V;
  // cal_dLCBarRef <<
  //   constraintModel.BwC.transpose()*fb.dwBfb,
  //   VectorXd::Zero(info.constraint->c.all),
  //   cal_dVmBarRef + constraintModel.dBm.transpose()*model->cal_V,
  //   BLC.transpose()*cal_dLCRef;

  ddqMoptRef = pInv(ACBar)*(cal_dLCBarRef - dACBar*model->dqM) + N(ACBar)*ddqthinit();
  VectorXd cal_dLCOpt = model->cal_AM*ddqMoptRef + model->cal_dAM*model->dqM;
  // VectorXd cal_dLCOpt = calAM*ddqMoptRef + caldAM*model->dqM;

  MatrixXd Sh = BLC*BLC.transpose();

  cal_dLCRef = cal_dLCOpt;
  // cal_dLCRef = Sh*cal_dLCRef + N(BLC.transpose())*cal_dLCOpt;

  // if((cal_dLCOpt-cal_dLCRef).norm()>0.00001){
  // o(cal_dLCOpt);
  // o(cal_dLCRef);
  // }
  // o(cal_dLCOpt);
  // o(cal_dLCRef);

  return ddqMoptRef;
}
