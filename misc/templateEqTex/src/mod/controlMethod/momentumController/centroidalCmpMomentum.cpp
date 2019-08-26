/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalCmpMomentum()
{
  if(debug) DEBUG;

  // Vector2d rCMPRef = rX.head(2) - drXDes.head(2)/wX - (KX*(rXDes - rX)).head(2);
  Vector2d rCMPRef = model->rX.head(2) - fb.drXfb.head(2)/model->wX;

  dpRef <<
    (model->M*worldModel->ag(2)/model->rC0(2))*(model->rC.head(2) - rCMPRef),
    model->M*fb.dvCfb(2);

  // dlCRef <<
  //   -model.hoap2.all.m*g*bbSx*(rCMPRef - rp),
  //   (IC*dwBRef)(2);
  centroidalAngularMomentum();

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
