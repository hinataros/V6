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
    if(!rBfinCur)
      rBpreDes = rBf;
    else
      rBpreDes = RB0.transpose()*(model->rB - rB0);
  }

  if(baseRotationNum==num){
    if(!qBfinCur)
      qBpreDes = qBf;
    else
      qBpreDes = qB0.inverse()*Quaternion4d::R2q(model->RB);
  }

  for(int i=0; i<info->controlNodeNum; i++){
    if(controlNodeTranslationNum[i]==num){
      if(!rfinCur[i]){
        rpreDes[i] = rf[i];
        rpreDesabs[i] = rfabs[i];
      }
      else{
        rpreDes[i] = RB0.transpose()*(model->r[i] - r0[i]);
        rpreDesabs[i] = model->r[i];
      }
    }
    if(controlNodeRotationNum[i]==num){
      if(!qfinCur[i]){
        qpreDes[i] = qf[i];
        qpreDesabs[i] = qfabs[i];
      }
      else{
        qpreDes[i] = qB0.inverse()*Quaternion4d::R2q(model->R[i]) * q0[i].inverse() * qB0;
        qpreDesabs[i] = Quaternion4d::R2q(model->R[i]);
      }
    }

    if(controlNodeForceNum[i]==num){
      if(!ffinCur[i])
        fpreDes[i] = ff[i];
      else
        fpreDes[i] = RB0.transpose()*model->cal_F.segment(i*6,3);
    }
    if(controlNodeMomentNum[i]==num){
      if(!nfinCur[i])
        npreDes[i] = nf[i];
      else
        npreDes[i] = model->cal_F.segment(3+i*6,3);
    }
  }

  if(comNum==num){
    if(!rCfinCur)
      rCpreDes = rCf;
    else
      rCpreDes = RB0.transpose()*(model->rC - rC0);
  }
  if(dcmNum==num){
    if(!rXfinCur){
      rXpreDes = rXf;
      rXpreDesabs = rXfabs;
    }
    else{
      rXpreDes = RB0.transpose()*(model->rX - rX0);
      rXpreDesabs = model->rX;
    }
  }

  if(externalWrenchNum==num) {
    cal_FextpreDes = cal_Fextf;
    // cal_FextpreDes = model->cal_Fext; //そんなものはない
  }
}


void RLS::DesiredValueGenerator::updatePres() // amiyata
{
  if(debug) DEBUG;

  rBpreDes = Vector3d::Zero();
  qBpreDes = Quaternion4d::Identity(); // Zeroじゃないので気をつけるよーに！！！！！！

  for(int i=0; i<info->controlNodeNum; i++){
    rpreDes[i] = Vector3d::Zero();
    qpreDes[i] = Quaternion4d::Identity();

    fpreDes[i] = Vector3d::Zero();
    npreDes[i] = Vector3d::Zero();
  }

  rCpreDes = Vector3d::Zero();
  rXpreDes = Vector3d::Zero();

  cal_FextpreDes = Vector6d::Zero();

  // amiyata final des reset （しないとrelが暴れる）
  rBf = Vector3d::Zero();
  qBf = Quaternion4d::Identity(); // Zeroじゃないので気をつけるよーに！！！！！！

  for(int i=0; i<info->controlNodeNum; i++){
    rf[i] = Vector3d::Zero();
    qf[i] = Quaternion4d::Identity();

    ff[i] = Vector3d::Zero();
    nf[i] = Vector3d::Zero();
  }

  rCf = Vector3d::Zero();
  rXf = Vector3d::Zero();

  cal_Fextf = Vector6d::Zero();

  // final absdes reset （しないとabsが暴れる）
  // rBfabs = model->rB;
  // qBfabs = Quaternion4d::R2q(model->RB); // そんなものはなかった・・・・

  for(int i=0; i<info->controlNodeNum; i++){
    rfabs[i] = model->r[i];
    qfabs[i] = Quaternion4d::R2q(model->R[i]);
  }

  rXfabs = model->rX;
}
