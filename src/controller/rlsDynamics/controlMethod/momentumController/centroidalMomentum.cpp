/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::centroidalMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  dpRef = model.hoap2.all.m*dvCRef;

  dlCRef = IC*dwBRef + dIC*model.hoap2.limb[0].node[0].w;
  // dlCRef = - KDlC*model.hoap2.all.lC;

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
