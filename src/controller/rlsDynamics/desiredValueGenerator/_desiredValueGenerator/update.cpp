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

  if(baseTranslationNum==num){
    rBpreDes = rBf;
    rBfinCur = model->rB;
  }

  if(baseRotationNum==num){
    qBpreDes = qBf;
    qBfinCur = Quaternion4d::R2q(model->RB); // あるか怪しい
  }

  for(int i=0; i<info->controlNodeNum; i++){
    if(controlNodeTranslationNum[i]==num){
      rpreDes[i] = rf[i];
      rfinCur[i] = model->r[i];
      rpreDesabs[i] = rfabs[i];
      rfinCurabs[i] = model->r[i] + r0[i];
    }
    if(controlNodeRotationNum[i]==num){
      qpreDes[i] = qf[i];
      qfinCur[i] = Quaternion4d::R2q(model->R[i]);
      qpreDesabs[i] = qfabs[i];
      qfinCurabs[i] = Quaternion4d::R2q(model->R[i]) + q0[i];

    }

    if(controlNodeForceNum[i]==num){
      fpreDes[i] = ff[i];
      ffinCur[i] = model->cal_F.segment(i*6,3);
    }
    if(controlNodeMomentNum[i]==num){
      npreDes[i] = nf[i];
      nfinCur[i] = model->cal_F.segment(3+i*6,3);
    }
  }

  if(comNum==num){
    rCpreDes = rCf;
    rCfinCur = model->rC;
  }
  if(dcmNum==num){
    rXpreDes = rXf;
    rXfinCur = model->rX;
  }

  if(externalWrenchNum==num) {
    cal_FextpreDes = cal_Fextf;
    // cal_FextfinCur = model->cal_Fext; //そんなものはない
  }
}
