/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameState(TreeModel &model)
{
  if(debug) DEBUG;

  rB = model.link[model.info.rootNode].r;
  xiB = R2xi(model.link[model.info.rootNode].R);

  cal_XB <<
    rB,
    xiB;

  vB = model.link[model.info.rootNode].v;
  wB = model.link[model.info.rootNode].w;

  cal_VB <<
    vB,
    wB;

  dq <<
    cal_VB,
    dth;

  rC = model.all.rC;
  vC = model.all.vC;

  cal_VM <<
    vC,
    wB;

  dqM <<
    cal_VM,
    dth;

  cal_VC <<
    vC,
    wB + IC.inverse()*HC*dth;
}
