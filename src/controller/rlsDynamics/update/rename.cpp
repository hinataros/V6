/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::rename()
{
  if(debug) DEBUG;

    // mixed
  // ******************************
  Pcf = cal_Pc.block(0,0,3,info.constraint.c.all);
  Pmf = cal_Pm.block(0,0,3,info.constraint.m.all);
  PcMm = cal_PcM.block(3,0,3,info.constraint.c.all);
  cal_JcM = cal_Jc - Pcf.transpose()*model->JB2C;
  cal_JmM = cal_Jm - Pmf.transpose()*model->JB2C;

  // diff
  dPcf = cal_dPc.block(0,0,3,info.constraint.c.all);
  dPmf = cal_dPm.block(0,0,3,info.constraint.m.all);
  dPcMm = cal_dPc.block(3,0,3,info.constraint.c.all);
  // dPcf = 0と仮定
  cal_dJcM = cal_dJc - Pcf.transpose()*model->dJB2C;
  cal_dJmM = cal_dJm - Pmf.transpose()*model->dJB2C;

  if(info.constraint.c.all){
    Jc <<
      cal_Pc.transpose(), cal_Jc;
    dJc <<
      cal_dPc.transpose(), cal_dJc;
    JcM <<
      cal_PcM.transpose(), cal_JcM;
    dJcM <<
      cal_dPcM.transpose(), cal_dJcM;
  }

  if(info.constraint.m.all){
    Jm <<
      cal_Pm.transpose(), cal_Jm;
    dJm <<
      cal_dPm.transpose(), cal_dJm;
    JmM <<
      cal_PmM.transpose(), cal_JmM;
    dJmM <<
      cal_dPmM.transpose(), cal_dJmM;
  }

  cal_JcHat = cal_Jc - cal_PcM.transpose()*model->Jth;
  cal_JmHat = cal_Jm - cal_PmM.transpose()*model->Jth;

  cal_dJcHat = cal_dJc - cal_dPcM.transpose()*model->Jth - cal_PcM.transpose()*model->dJth;
  cal_dJmHat = cal_dJm - cal_dPmM.transpose()*model->Jth - cal_PmM.transpose()*model->dJth;

  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!info.constraint.c.axis[i]==0)
      bb_ScB(i,i) = 1;
}
