/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::zeroMotion(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  return VectorXd::Zero(info.dof.all);
}
