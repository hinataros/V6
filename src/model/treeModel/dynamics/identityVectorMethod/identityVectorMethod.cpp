#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::identityVectorMethod(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  VectorXd cal_Q = VectorXd::Zero(info.dof.all);
  VectorXd ddq = VectorXd::Zero(info.dof.all);

  cal_Q = recursiveNewtonEuler(config, info, ddq.head(3), ddq.segment(3,3), ddq.tail(info.dof.joint));

  all.b = cal_Q;

  for(int i=0; i<info.dof.all; i++){
    ddq(i) = 1.;

    cal_Q = recursiveNewtonEuler(config, info, ddq.head(3), ddq.segment(3,3), ddq.tail(info.dof.joint));
    all.M.col(i) = cal_Q - all.b;

    ddq = VectorXd::Zero(info.dof.all);
  }

  all.g = gravity(config, info);
  all.c = all.b - all.g;
}
