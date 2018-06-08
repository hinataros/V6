/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalAngularMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  dlCRef = cross((Vector3d() << rp, 0.).finished() - model.hoap2.all.rC)*dpRef;
  dlCRef += IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w;
  // dlCRef = IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w;
  // dlCRef = -KDlC*model.hoap2.all.lC;
}
