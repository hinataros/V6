/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalCmpMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // Vector2d rCMPRef = rX.head(2) - drXDes.head(2)/wX - (KX*(rXDes - rX)).head(2);
  Vector2d rCMPRef = rX.head(2) - drXRef.head(2)/wX;

  dpRef <<
    (model.hoap2.all.m*g/rC0(2))*(model.hoap2.all.rC.head(2) - rCMPRef),
    model.hoap2.all.m*dvCRef(2);

  // dlCRef <<
  //   -model.hoap2.all.m*g*bbSx*(rCMPRef - rp),
  //   (IC*dwBRef)(2);
  centroidalAngularMomentum(config, info, model);

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
