/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::vrp_CRB(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->vrpMomentum();
  CRB_AM(io);

  io->cal_dLCRef <<
    io->dpRef,
    io->dlCRef;
}
