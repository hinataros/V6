/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::ankleHipStratagy(Config &config, Info &info, Model &model, double &t)
{
  double d = 0.008;
  // double d = 0.01;
  if(rp(0)>=0.058-d || rp(0)<=-0.040+d)
    flagHip = true;

  if(flagHip==false && cal_FextRef.norm()==0.){
    if(flagInit)
      // default and initial state
      return 0;

    // else{
    //   if(info.sim.state==2 && t>info.sim.trev+info.sim.trecf)
    //     flagInit = true;

    //   return 2;
    // }
  }

  if(flagHip==true && flagStay==false){
    if(info.sim.state==2 && t>info.sim.trev+info.sim.trecf){
      flagInit = true;
      flagHip = false;
      flagStay = true;
    }

    return 2;
  }

  if(flagHip==false && cal_FextRef.norm()!=0.){
    flagInit = false;

    if(flagStay)
      return 0;

    return 1;
  }

  return -1;
}
