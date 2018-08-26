/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseDcmMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  dcmMomentum(info);
  baseAngularMomentum(info);

  cal_dLBRef <<
    dpRef,
    dlBRef;
}
