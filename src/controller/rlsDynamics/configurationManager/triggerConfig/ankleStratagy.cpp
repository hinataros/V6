/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::ankleStratagy(Config &config, Info &info, Model &model, double &t)
{
  // default and initial state
  if(flagInit==true && cal_FextRef.norm()==0.){
    return 0;
  }

  if(flagInit==false && cal_FextRef.norm()==0.){
    if(info.sim.state==2 && t>info.sim.trev+info.sim.trecf){
      flagInit = true;
    }
    return 2;
  }

  if(cal_FextRef.norm()!=0.){
    flagInit=false;

    return 1;
  }

  return -1;
}
