/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controllerTreeModel.hpp"

void RLS::ControllerTreeModel::cop()
{
  if(debug) DEBUG;

  double rpDenominator = 0.;
  Vector2d rpNumerator = Vector2d::Zero();
  Vector6d cal_Fk = Vector6d::Zero();

  for(int i=0; i<info->sensorNodeNum; i++){
    cal_Fk = cal_Fsensor.segment(6*i, 6);

    // foot net CoP
    if(i==2||i==3)
      cal_Fk = Vector6d::Zero();

    if(cal_Fk(2) != 0.){
      rpk.segment(2*i, 2) <<
        -cal_Fk(4)/cal_Fk(2),
         cal_Fk(3)/cal_Fk(2);

      rpw2k.segment(2*i, 2) <<
        (-cal_Fk(4)/cal_Fk(2)) + rsensor[i](0),
        (cal_Fk(3)/cal_Fk(2)) + rsensor[i](1);

      rpNumerator(0) += rpw2k(2*i)*cal_Fk(2);
      rpNumerator(1) += rpw2k(2*i+1)*cal_Fk(2);
      rpDenominator += cal_Fk(2);
    }
    else{
      rpk.segment(2*i, 2) << NAN, NAN;
      rpw2k.segment(2*i, 2) << NAN, NAN;
    }
  }

  if(rpDenominator != 0.)
    rp = rpNumerator/rpDenominator;

  else
    rp <<
      NAN, NAN;
}
