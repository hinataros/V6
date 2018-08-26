/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalAngularMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // dlCRef = cross((Vector3d() << rp, 0.).finished() - model.hoap2.all.rC)*dpRef + IC*dwBRef;
  // dlCRef = cross((Vector3d() << rp, 0.).finished() - model.hoap2.all.rC)*dpRef;
  // dlCRef += IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w;

  // dlCRef =
  //   cross((Vector3d() << rp, 0.).finished() - model.hoap2.all.rC)*dpRef
  //   - KDlC*(HC*model.hoap2.all.dth);
  // dlCRef = IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w - KDlC*(IC*model.hoap2.limb[0].node[0].w + HC*model.hoap2.all.dth);
  dlCRef = IC*dwBRef + dIC*wB - KDlC*HC*dth;
  // dlCRef = IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w + HC*ddthRef + dHC*model.hoap2.all.dth;
  // dlCRef = IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w;
  // dlCRef = -KDlC*model.hoap2.all.lC;
}
