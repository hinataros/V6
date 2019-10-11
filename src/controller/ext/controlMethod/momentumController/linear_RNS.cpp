/**
   @author Ryotaro Hinata 2019
*/

#include "_ext.hpp"

void RLS::Ext::linear_RNS(RlsDynamics *io)
{
  if(debug) DEBUG;

  io->linearMomentum();
  SAM_RNS(io);

  io->cal_dLCRef <<
    io->dpRef,
    io->dlCRef;
}
