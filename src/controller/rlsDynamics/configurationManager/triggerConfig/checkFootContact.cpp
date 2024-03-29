/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::checkFootContact(const double &t, const struct State &state)
{
  if(debug) DEBUG;

  if(contactFlag[0]==true&&contactFlag[1]==true)
    return 1;

  if(contactFlag[0]==false&&contactFlag[1]==true)
    return 2;
  if(contactFlag[0]==true&&contactFlag[1]==false)
    return 3;

  return 0;
}
