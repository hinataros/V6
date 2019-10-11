/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::vrp_Damper(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->vrpMomentum();
  SAM_Damper(io);

  systemAngularMomentumLimitation(io);

  io->cal_dLCRef <<
    io->dpRef,
    io->dlCRef;
}
