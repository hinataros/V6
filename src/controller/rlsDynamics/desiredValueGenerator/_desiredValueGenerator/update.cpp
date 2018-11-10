/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::update(const double &t)
{
  // state.rCpreDes = model->rC - rC0;
  // state.vCpreDes = model->vC;

  // state.rBpreDes = model->rB - rB0;
  // state.vBpreDes = model->vB;
  // state.xiBpreDes = R2xi(model->RB) - xiB0;
  // state.dxiBpreDes = w2dxi(model->wB, R2xi(model->RB));

  // state.rXpreDes = model->rX - rX0;
  // // smiyahara: いつか変える
  // state.drXpreDes = drXDes;

  // state.cal_XpreDes = model->cal_X - cal_X0;
  // state.cal_VpreDes = model->cal_V;
}

void RLS::DesiredValueGenerator::update(const double &t, const int &num)
{
  if(debug) DEBUG;

  tw0[num] = t;

  if(baseTranslationNum==num)
    rBpreDes = rBf;

  if(baseRotationNum==num)
    qBpreDes = qBf;

  for(int i=0; i<info->controlNodeNum; i++){
    if(controlNodeTranslationNum[i]==num){
      rpreDes[i] = rf[i];
      rpreDesabs[i] = model->r[i];
    }
    if(controlNodeRotationNum[i]==num){
      qpreDes[i] = qf[i];
      qpreDesabs[i] = Quaternion4d::R2q(model->R[i]);
    }

    if(controlNodeForceNum[i]==num)
      fpreDes[i] = ff[i];
    if(controlNodeMomentNum[i]==num)
      npreDes[i] = nf[i];
  }

  if(comNum==num)
    rCpreDes = rCf;
  if(dcmNum==num)
    rXpreDes = rXf;

  if(externalWrenchNum==num)
    cal_FextpreDes = cal_Fextf;
}
