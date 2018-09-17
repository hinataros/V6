/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::renameState(const TreeModel &model)
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

  // mixed
  // ******************************
  Pcf = cal_Pc.block(0,0,3,model.info.contact.c.all);
  Pmf = cal_Pm.block(0,0,3,model.info.contact.m.all);
  PcMm = cal_PcM.block(3,0,3,model.info.contact.c.all);
  cal_JcM = cal_Jc - Pcf.transpose()*model.all.JB2C;
  cal_JmM = cal_Jm - Pmf.transpose()*model.all.JB2C;

  // diff
  dPcf = cal_dPc.block(0,0,3,model.info.contact.c.all);
  dPmf = cal_dPm.block(0,0,3,model.info.contact.m.all);
  dPcMm = cal_dPc.block(3,0,3,model.info.contact.c.all);
  // dPcf = 0と仮定
  cal_dJcM = cal_dJc - Pcf.transpose()*model.all.dJB2C;
  cal_dJmM = cal_dJm - Pmf.transpose()*model.all.dJB2C;
}
