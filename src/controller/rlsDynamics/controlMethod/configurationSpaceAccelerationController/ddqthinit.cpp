/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddqthinit()
{
  if(debug) DEBUG;

  VectorXd ddthinit = -KDth*model->dth + Kthinit*(model->th0 - model->th);

  return (VectorXd(info.model.dof.all)<<Vector6d::Zero(), ddthinit).finished();
  // return (VectorXd(info.model.dof.all)<<Vector3d::Zero(), fb.dwBfb, ddthinit).finished();
}
