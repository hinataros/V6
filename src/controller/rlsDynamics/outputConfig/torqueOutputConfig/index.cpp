/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputIndexConfig(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;
  dc_list.pCRB = model.hoap2.all.m*cal_VM.head(3);
  dc_list.lCRB = IC*cal_VM.tail(3);

  dc_list.pCth = Vector3d::Zero();
  dc_list.lCth = HC*model.hoap2.all.dth;

  dc_list.p = model.hoap2.all.m*cal_VM.head(3);
  dc_list.lC = IC*cal_VM.tail(3) + HC*model.hoap2.all.dth;

  // cop
  dc_list.rp = rp;

  // replace x <==> y
  dc_list.rpk = VectorXd::Zero(2*info.value.joint);
  for(int i=0; i<info.value.joint; i++)
    dc_list.rpk.segment(2*i, 2) = antiDiag(2,1.,1.)*rpk.segment(2*i, 2);

  dc_list.rpkx = dc_list.rpky
    = VectorXd::Zero(1*info.value.joint);
  for(int i=0; i<info.value.joint; i++){
    dc_list.rpkx(i) = rpk(2*i);
    dc_list.rpky(i) = rpk(2*i+1);
  }

  // cmp
  dc_list.rcmp = rcmp;

  // dcm
  dc_list.rX = rX;
}
