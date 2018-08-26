/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputIndexConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  dc_list.pCRB = M*vC;
  dc_list.lCRB = IC*wB;

  dc_list.pCth = Vector3d::Zero();
  dc_list.lCth = HC*dth;

  dc_list.p = M*vC;
  dc_list.lC = IC*wB + HC*dth;

  // cop
  dc_list.rp = rp;

  // replace x <==> y
  dc_list.rpk = VectorXd::Zero(2*info.eeNum);
  for(int i=0; i<info.eeNum; i++)
    dc_list.rpk.segment(2*i, 2) = rpk.segment(2*i, 2);

  dc_list.rpkx = dc_list.rpky
    = VectorXd::Zero(1*info.eeNum);
  for(int i=0; i<info.eeNum; i++){
    dc_list.rpkx(i) = rpk(2*i);
    dc_list.rpky(i) = rpk(2*i+1);
  }

  // cmp
  dc_list.rcmp = rcmp;

  // dcm
  dc_list.rX = rX;
}
