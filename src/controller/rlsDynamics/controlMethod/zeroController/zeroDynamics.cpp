/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::zeroDynamics(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  return VectorXd::Zero(tau.size());
}
