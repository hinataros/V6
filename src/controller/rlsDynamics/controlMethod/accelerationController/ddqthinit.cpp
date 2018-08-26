/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqthinit(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  VectorXd ddthinit = -KDth*dth + Kthinit*(th0 - th);

  return (VectorXd(info.dof.all)<<Vector6d::Zero(), ddthinit).finished();
}
