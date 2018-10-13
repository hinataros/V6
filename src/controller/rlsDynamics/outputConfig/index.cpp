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
  outputList.lCth = model->HC*model->dth;

  outputList.p = model->M*model->vC;
  outputList.lC = model->IC*model->wB + model->HC*model->dth;

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

  // cmp
  outputList.rcmp = model->rcmp;

  // dcm
  outputList.rX = model->rX;
}
