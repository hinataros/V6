/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cop(const TreeModel &model)
{
  if(debug) DEBUG;

  double rpDenominator = 0.;
  Vector2d rpNumerator = Vector2d::Zero();
  Vector6d cal_Fk = Vector6d::Zero();
  // sensor position w.r.t. world coordinates
  Vector3d rSensor = Vector3d::Zero();

  for(int i=0; i<model.info.controlNodeNum; i++){
    cal_Fk = cal_F.segment(6*i, 6);
    // smiyahara: 先端部と仮定． 他の場所で定義したほうがいいかも
    rSensor = cal_X.segment(6*i, 3);

    if(cal_Fk(2) != 0.){
      rpk.segment(2*i, 2) <<
        -cal_Fk(4)/cal_Fk(2),
        cal_Fk(3)/cal_Fk(2);

      rpw2k.segment(2*i, 2) <<
        (-cal_Fk(4)/cal_Fk(2)) + rSensor(0),
        (cal_Fk(3)/cal_Fk(2)) + rSensor(1);

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
