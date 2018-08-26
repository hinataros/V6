/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  linearMomentum(info);
  baseAngularMomentum(info);

  cal_dLBRef <<
    dpRef,
    dlBRef;
}
