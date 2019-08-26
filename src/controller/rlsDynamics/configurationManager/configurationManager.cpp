/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

#include "_ext.hpp"

bool RLS::RlsDynamics::configurationManager(const double &t)
{
  if(debug) DEBUG;

  if(stateTrigger(t, topState)){
    des.mapping();
    fb.mapping();
    mapping();

    return true;
  }

  return false;
}
