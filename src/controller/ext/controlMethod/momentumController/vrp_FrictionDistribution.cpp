/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::vrp_FrictionDistribution(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->vrpMomentum();
  SAM_FrictionDistribution(io);

  io->cal_dLCRef <<
    io->dpRef,
    io->dlCRef;
}
