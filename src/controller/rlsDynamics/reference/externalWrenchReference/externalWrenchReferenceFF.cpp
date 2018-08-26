/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::externalWrenchReferenceFF(TreeModel &model)
{
  if(debug) DEBUG;

  cal_FextRef = cal_FextDes;

  Vector3d rB2P = Vector3d::Zero();
  rB2P <<
    0., 0., 0.145;

  Vector3d rW2P = Vector3d::Zero();
  rW2P = cal_XB.head(3) + model.link[model.info.rootNode].R*rB2P;

  // rW2P <<
  //   0., -0.039, 0.;
  // rW2CP <<
  //   model.all.rC(0) - cal_X(0),
  //   0.,
  //   model.all.rC(2) - cal_X(2);

  // if(t==0.)
    // cal_FextRef <<
    //   1.,0.,0.,0.,0.,0.;

  virtualInput <<
    cal_FextRef.head(3),
    cal_FextRef.tail(3) + cross(rW2P)*cal_FextRef.head(3);
}
