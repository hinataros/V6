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
  Ccf = mbb_Cc.block(0,0,3,info.constraint.c.all);
  Cmf = mbb_Cm.block(0,0,3,info.constraint.m.all);
  CcMm = mbb_CcM.block(3,0,3,info.constraint.c.all);
  cal_JcM = cal_Jc - Ccf.transpose()*model->JB2C;
  cal_JmM = cal_Jm - Cmf.transpose()*model->JB2C;

  // diff
  dCcf = mbb_dCc.block(0,0,3,info.constraint.c.all);
  dCmf = mbb_dCm.block(0,0,3,info.constraint.m.all);
  dCcMm = mbb_dCc.block(3,0,3,info.constraint.c.all);
  // dCcf = 0と仮定
  cal_dJcM = cal_dJc - Ccf.transpose()*model->dJB2C;
  cal_dJmM = cal_dJm - Cmf.transpose()*model->dJB2C;

  if(info.constraint.c.all){
    Jc <<
      mbb_Cc.transpose(), cal_Jc;
    dJc <<
      mbb_dCc.transpose(), cal_dJc;
    JcM <<
      mbb_CcM.transpose(), cal_JcM;
    dJcM <<
      mbb_dCcM.transpose(), cal_dJcM;
  }

  if(info.constraint.m.all){
    Jm <<
      mbb_Cm.transpose(), cal_Jm;
    dJm <<
      mbb_dCm.transpose(), cal_dJm;
    JmM <<
      mbb_CmM.transpose(), cal_JmM;
    dJmM <<
      mbb_dCmM.transpose(), cal_dJmM;
  }

  cal_JcHat = cal_Jc - mbb_CcM.transpose()*model->Jth;
  cal_JmHat = cal_Jm - mbb_CmM.transpose()*model->Jth;

  cal_dJcHat = cal_dJc - mbb_dCcM.transpose()*model->Jth - mbb_CcM.transpose()*model->dJth;
  cal_dJmHat = cal_dJm - mbb_dCmM.transpose()*model->Jth - mbb_CmM.transpose()*model->dJth;

  // forward kinematics for kinematics simulation
  for(int i=0; i<6; i++)
    if(!info.constraint.c.axis[i]==0)
      bb_ScB(i,i) = 1;
}
