/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::ddthD()
{
  if(debug) DEBUG;

  return -KDth*model->dth;
}
