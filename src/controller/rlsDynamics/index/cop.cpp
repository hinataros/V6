#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cop(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  double rpDenominator = 0.;
  Vector2d rpNumerator = Vector2d::Zero();
  Vector6d cal_Fk = Vector6d::Zero();

  for(int i=1; i<info.value.node; i++){
    cal_Fk = cal_F.segment((6*(i-1)), 6);

    if(cal_Fk(2) != 0.){
      rpk.segment(2*(i-1), 2) <<
	-cal_Fk(4) / cal_Fk(2),
	cal_Fk(3) / cal_Fk(2);

      rpNumerator(0) += (rpk(2*(i-1)) + cal_X(6*(i-1)))*cal_Fk(2);
      rpNumerator(1) += (rpk(2*(i-1)+1) + cal_X(6*(i-1))+1)*cal_Fk(2);
      rpDenominator += cal_Fk(2);
    }
  }

  if(rpDenominator != 0.)
    rp = rpNumerator / rpDenominator;

  else
    rp = model.all.rC.head(2);
}
