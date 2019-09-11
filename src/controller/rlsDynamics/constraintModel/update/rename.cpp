/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "constraintModel.hpp"

void RLS::ConstraintModel::rename()
{
  if(debug) DEBUG;

  // mixed
  // ******************************
  Pcf = mbb_Cc.block(0,0,3,info.constraint.c.all);
  Pmf = mbb_Cm.block(0,0,3,info.constraint.m.all);
  PcMm = mbb_CcM.block(3,0,3,info.constraint.c.all);
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
      mbb_Cc.transpose(), cal_Jc;
    dJc <<
      cal_dPc.transpose(), cal_dJc;
    JcM <<
      mbb_CcM.transpose(), cal_JcM;
    dJcM <<
      cal_dPcM.transpose(), cal_dJcM;
  }

  if(info.constraint.m.all){
    Jm <<
      mbb_Cm.transpose(), cal_Jm;
    dJm <<
      cal_dPm.transpose(), cal_dJm;
    JmM <<
      mbb_CmM.transpose(), cal_JmM;
    dJmM <<
      cal_dPmM.transpose(), cal_dJmM;
  }

  cal_JcHat = cal_Jc - mbb_CcM.transpose()*model->Jth;
  cal_JmHat = cal_Jm - mbb_CmM.transpose()*model->Jth;

  cal_dJcHat = cal_dJc - cal_dPcM.transpose()*model->Jth - mbb_CcM.transpose()*model->dJth;
  cal_dJmHat = cal_dJm - cal_dPmM.transpose()*model->Jth - mbb_CmM.transpose()*model->dJth;

  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!info.constraint.c.axis[i]==0)
      bb_ScB(i,i) = 1;
}
