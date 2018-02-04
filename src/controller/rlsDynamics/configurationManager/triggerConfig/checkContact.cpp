/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::checkContact(Config &config, Info &info, Model &model, double &t)
{
  // default and initial state
  info.contact.num = 0;
  for(int i=0; i<info.value.joint; i++)
    if(cal_F(6*i+2)!=0.)
      info.contact.num++;

  if(info.contact.num)
    return 1;

  return 0;
}
