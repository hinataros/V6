/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqD(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  VectorXd dqth = VectorXd::Zero(info.dof.all);
  dqth.tail(info.dof.joint) = model.hoap2.all.dth;

  return -KDq*dqth;
}
