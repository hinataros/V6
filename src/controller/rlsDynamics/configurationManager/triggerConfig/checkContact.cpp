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
  for(int i=0; i<info.value.joint; i++){
    if(cal_F(6*i+2)!=0.){
      info.limb[i].contact = true;
      info.contact.num++;
    }
    else
      info.limb[i].contact = false;
  }

  if(info.sim.phase==4){
    if(info.limb[0].contact==true&&info.limb[1].contact==true){
      o(rpk);
      gc;
    }
  }

  double flmax = 5.7e-2;
  double flmin = -3.1e-2;
  double sl = 3.05e-2;
  if(info.limb[0].contact==true&&info.limb[1].contact==true){
    if(info.sim.phase==4){
      if(rpk(0)<flmax&&rpk(0)>flmin&&abs(rpk(1))<sl
         &&rpk(2)<flmax&&rpk(2)>flmin&&abs(rpk(3))<sl){
        return 1;
      }
      else{
        if(rpk(2)<flmax&&rpk(2)>flmin&&abs(rpk(3))<sl){
          if(rpk(0)>flmax||rpk(0)<flmin&&abs(rpk(1))>sl)
            return 2;
          else if(rpk(0)>flmax||rpk(0)<flmin&&abs(rpk(1))<sl)
            return 3;
          else if(rpk(0)<flmax&&rpk(0)>flmin&&abs(rpk(1))>sl)
            return 4;
        }
        if(rpk(0)<flmax&&rpk(0)>flmin&&abs(rpk(1))<sl){
          if(rpk(2)>flmax||rpk(2)<flmin&&abs(rpk(3))>sl)
            return 6;
          else if(rpk(2)>flmax||rpk(2)<flmin&&abs(rpk(3))<sl)
            return 7;
          else if(rpk(2)<flmax&&rpk(2)>flmin&&abs(rpk(3))>sl)
            return 8;
        }
      }
    }
    return 1;
  }

  if(info.limb[0].contact==false&&info.limb[1].contact==true)
    return 5;
  if(info.limb[0].contact==true&&info.limb[1].contact==false)
    return 9;

  // if(info.contact.num==2)
  //   return 1;

  // if(info.contact.num==1)
  //   return 2;

  // if(info.contact.num)
  //   return 1;

  return 0;
}
