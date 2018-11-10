/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::transformExternalWrench()
{
  if(debug) DEBUG;

  Vector3d rB2P = Vector3d::Zero();
  rB2P <<
    0., 0., 0.145;

  Vector3d rW2P = Vector3d::Zero();
  rW2P = model->rB + model->RB*rB2P;

  // rW2P <<
  //   0., -0.039, 0.;
  // rW2CP <<
  //   model.all.rC(0) - cal_X(0),
  //   0.,
  //   model.all.rC(2) - cal_X(2);

  virtualInput <<
    fb.cal_Fextfb.head(3),
    fb.cal_Fextfb.tail(3) + cross(rW2P)*fb.cal_Fextfb.head(3);
}
