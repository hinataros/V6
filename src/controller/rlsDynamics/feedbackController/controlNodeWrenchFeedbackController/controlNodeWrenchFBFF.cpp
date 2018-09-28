/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::controlNodeWrenchFBFF(const TreeModel &model)
{
  if(debug) DEBUG;

  cal_FRef = cal_FDes;
}
