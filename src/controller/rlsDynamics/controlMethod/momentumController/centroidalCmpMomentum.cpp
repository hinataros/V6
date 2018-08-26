/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalCmpMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // Vector2d rCMPRef = rX.head(2) - drXDes.head(2)/wX - (KX*(rXDes - rX)).head(2);
  Vector2d rCMPRef = rX.head(2) - drXRef.head(2)/wX;

  dpRef <<
    (M*g/rC0(2))*(rC.head(2) - rCMPRef),
    M*dvCRef(2);

  // dlCRef <<
  //   -model.hoap2.all.m*g*bbSx*(rCMPRef - rp),
  //   (IC*dwBRef)(2);
  centroidalAngularMomentum(info);

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
