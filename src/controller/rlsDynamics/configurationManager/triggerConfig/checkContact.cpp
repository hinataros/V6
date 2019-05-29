/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::checkContact(const double &t)
{
  if(debug) DEBUG;

  // bool contactFlag[info.model.controlNodeNum]; //amiyata staticへ

  for(int i=0; i<info.model.controlNodeNum; i++){
    if(model->cal_F(6*i+2)!=0.) {
      if(contactFlag[i]==false && i < 2)
        footPrintList.push_back(model->r[i]);
      contactFlag[i] = true;
    } else
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
    if(contactFlag[0]==true&&contactFlag[1]==true)
      return 4;

    if(contactFlag[0]==false&&contactFlag[1]==true)
      return 5;
    if(contactFlag[0]==true&&contactFlag[1]==false)
      return 6;
  }

  return 0;
}
