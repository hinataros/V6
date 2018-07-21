/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::walkHT(Config &config, Info &info, Model &model, double &t)
{
  // default and initial state
  info.contact.num = 0;
  for(int i=0; i<info.value.joint; i++){
    if(cal_F(6*i+2)!=0.){
      info.limb[i].contact = true;
      info.contact.num++;
    }
    else
      info.limb[i].contact = false;
  }

  // double hoge = 0.05;
  if(info.limb[0].contact==true&&info.limb[1].contact==true){
    // if(abs(cal_X.segment(6*0+3, 3)(1))>hoge*DEG2RAD)
    //   return 4;
    // else if(abs(cal_X.segment(6*1+3, 3)(1))>hoge*DEG2RAD)
    //   return 5;

    return 1;
  }

  if(info.limb[0].contact==false&&info.limb[1].contact==true)
    return 2;
  if(info.limb[0].contact==true&&info.limb[1].contact==false)
    return 3;

  return 0;
}
