/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqthD()
{
  if(debug) DEBUG;

  VectorXd ddthD = -KDth*model->dth;

  return (VectorXd(info.model.dof.all)<<Vector6d::Zero(), ddthD).finished();
}
