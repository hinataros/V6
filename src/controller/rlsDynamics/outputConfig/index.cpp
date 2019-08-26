/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputIndexConfig()
{
  if(debug) DEBUG;

  outputList.pCRB = model->M*model->vC;
  outputList.lCRB = model->IC*model->wB;

  outputList.pCth = Vector3d::Zero();
  outputList.lTh = model->HC*model->dth;

  if(model->dth.rows() == 20) {
    outputList.lThF = model->HC.block(0,0, 3,12) * model->dth.segment(0,12);
    outputList.lThH = model->HC.block(0,12, 3,8) * model->dth.segment(12,8);
  }

  outputList.p = model->M*model->vC;
  outputList.lC = model->IC*model->wB + model->HC*model->dth;

  outputList.wC = model->wB + model->IC.inverse()*model->HC*model->dth;

  // cop
  outputList.rp = model->rp;

  outputList.rpk = VectorXd::Zero(2*info.model.sensorNodeNum);
  for(int i=0; i<info.model.sensorNodeNum; i++)
    outputList.rpk.segment(2*i, 2) = model->rpk.segment(2*i, 2);

  outputList.rpw2k = VectorXd::Zero(2*info.model.sensorNodeNum);
  for(int i=0; i<info.model.sensorNodeNum; i++)
    outputList.rpw2k.segment(2*i, 2) = model->rpw2k.segment(2*i, 2);

  outputList.rpkx = outputList.rpky
    = VectorXd::Zero(1*info.model.sensorNodeNum);
  for(int i=0; i<info.model.sensorNodeNum; i++){
    outputList.rpkx(i) = model->rpk(2*i);
    outputList.rpky(i) = model->rpk(2*i+1);
  }

  outputList.th = model->th;
  outputList.dth = model->dth;

  // cmp
  outputList.rcmp = model->rcmp;

  // dcm
  outputList.rX = model->rX;
}
