/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::vrp_RNS(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->vrpMomentum();
  SAM_RNS(io);

  io->cal_dLCRef <<
    io->dpRef,
    io->dlCRef;
}
