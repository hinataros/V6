/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqthD(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  VectorXd ddthD = -KDth*dth;

  return (VectorXd(info.dof.all)<<Vector6d::Zero(), ddthD).finished();
}
