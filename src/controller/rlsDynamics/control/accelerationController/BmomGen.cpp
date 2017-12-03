#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::BmomGen(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd AB = MatrixXd::Zero(6, info.dof.all);
  AB <<
    model.hoap2.all.M.block(0,0,6,info.dof.all);

  MatrixXd ABBar = MatrixXd::Zero(6+c, info.dof.all);
  ABBar <<
    AB,
    Jc;

  MatrixXd dAB = MatrixXd::Zero(6, info.dof.all);
  dAB <<
    model.hoap2.all.dM.block(0,0,6,info.dof.all);

  MatrixXd dABBar = MatrixXd::Zero(6+c, info.dof.all);
  dABBar <<
    dAB,
    dJc;

  VectorXd dq = VectorXd::Zero(info.dof.all);
  dq <<
    cal_VB,
    model.hoap2.all.dth;

  VectorXd cal_dLBBarRef = VectorXd::Zero(6+c);
  cal_dLBBarRef.head(6) = cal_dLBRef;

  ddqRef = pInv(ABBar)*(cal_dLBBarRef - dABBar*dq) + N(ABBar)*ddqD(config, info, model);

  // ddqRef = VectorXd::Zero(info.dof.all);

  return ddqRef;
}
