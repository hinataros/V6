/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputErrConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  dc_list.erB = erB;
  dc_list.evB = evB;
  dc_list.eoB = eoB;
  dc_list.ewB = ewB;

  dc_list.eX = eX;

  dc_list.erC = erC;
  dc_list.evC = evC;

  dc_list.er = dc_list.ev
    = dc_list.eo = dc_list.ew
    = dc_list.ef = dc_list.en
    = VectorXd::Zero(3*info.eeNum);

  for(int i=0; i<info.eeNum; i++){
    dc_list.er.segment(3*i, 3) = cal_Ep.segment(6*i, 3);
    dc_list.eo.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*cal_Ep.segment(6*i+3, 3);

    dc_list.ev.segment(3*i, 3) = cal_Ev.segment(6*i, 3);
    dc_list.ew.segment(3*i, 3) = cal_Ev.segment(6*i+3, 3);

    dc_list.ef.segment(3*i, 3) = (Bc_k*cal_FcBarRef - cal_F).segment(6*i, 3);
    dc_list.en.segment(3*i, 3) = (Bc_k*cal_FcBarRef - cal_F).segment(6*i+3, 3);
  }
}
