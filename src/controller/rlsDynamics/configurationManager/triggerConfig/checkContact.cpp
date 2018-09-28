/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::checkContact(const Model &model, const double &t)
{
  bool contactFlag[model.hoap2.info.controlNodeNum];
  for(int i=0; i<model.hoap2.info.controlNodeNum; i++){
    if(cal_F(6*i+2)!=0.)
      contactFlag[i] = true;
    else
      contactFlag[i] = false;
  }

  if(contactFlag[2]==false){
    if(contactFlag[0]==true&&contactFlag[1]==true)
      return 1;

    if(contactFlag[0]==false&&contactFlag[1]==true)
      return 2;
    if(contactFlag[0]==true&&contactFlag[1]==false)
      return 3;
  }
  else{
    return 4;
  }

  return 0;
}
