/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cop(Config &config, Info &info, TreeModel &hoap2)
{
  if(config.flag.debug) DEBUG;

  double rpDenominator = 0.;
  Vector2d rpNumerator = Vector2d::Zero();
  Vector6d cal_Fk = Vector6d::Zero();
  // sensor position w.r.t. world coordinates
  Vector3d rSensor = Vector3d::Zero();

  for(int i=1; i<info.value.node; i++){
    cal_Fk = cal_F.segment((6*(i-1)), 6);
    // smiyahara: 先端部と仮定． 他の場所で定義したほうがいいかも
    rSensor = cal_X.segment((6*(i-1)), 3);

    if(cal_Fk(2) != 0.){
      rpk.segment(2*(i-1), 2) <<
        -cal_Fk(4)/cal_Fk(2),
        cal_Fk(3)/cal_Fk(2);

      rpw2k.segment(2*(i-1), 2) <<
        (-cal_Fk(4)/cal_Fk(2)) + rSensor(0),
        (cal_Fk(3)/cal_Fk(2)) + rSensor(1);

      rpNumerator(0) += rpw2k(2*(i-1))*cal_Fk(2);
      rpNumerator(1) += rpw2k(2*(i-1)+1)*cal_Fk(2);
      rpDenominator += cal_Fk(2);
    }
  }

  if(rpDenominator != 0.)
    rp = rpNumerator/rpDenominator;

  else
    rp = hoap2.all.rC.head(2);
}
