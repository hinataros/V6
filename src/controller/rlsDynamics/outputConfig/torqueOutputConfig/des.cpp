/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputDesConfig(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  dc_list.rBDes = rBDes;
  dc_list.vBDes = vBDes;
  dc_list.dvBDes = dvBDes;

  dc_list.xiBDes = antiDiag(3,1.,1.,1.)*xiBDes;
  dc_list.wBDes = wBDes;
  dc_list.dwBDes = dwBDes;

  dc_list.rCDes = rCDes;
  dc_list.vCDes = vCDes;
  dc_list.dvCDes = dvCDes;

  dc_list.rXDes = rXDes;
  dc_list.drXDes = drXDes;

  dc_list.rvrpDes = rX - drXDes/wX;

  dc_list.rDes = dc_list.vDes = dc_list.dvDes
    = dc_list.xiDes = dc_list.wDes = dc_list.dwDes
    = VectorXd::Zero(3*info.value.joint);

  for(int i=0; i<info.value.joint; i++){
    dc_list.rDes.segment(3*i, 3) = cal_XDes.segment(6*i, 3);
    dc_list.xiDes.segment(3*i, 3) = antiDiag(3,1.,1.,1.)*cal_XDes.segment(6*i+3, 3);

    dc_list.vDes.segment(3*i, 3) = cal_VDes.segment(6*i, 3);
    dc_list.wDes.segment(3*i, 3) = cal_VDes.segment(6*i+3, 3);

    dc_list.dvDes.segment(3*i, 3) = cal_dVDes.segment(6*i, 3);
    dc_list.dwDes.segment(3*i, 3) = cal_dVDes.segment(6*i+3, 3);
  }
}
