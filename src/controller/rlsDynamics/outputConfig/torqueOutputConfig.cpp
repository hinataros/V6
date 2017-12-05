#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputConfig(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  // desired values
  dc_list.rBDes = rBDes;
  dc_list.vBDes = vBDes;
  dc_list.dvBDes = dvBDes;

  dc_list.xiBDes = xiBDes;
  dc_list.wBDes = wBDes;
  dc_list.dwBDes = dwBDes;

  dc_list.cal_XDes = cal_XDes;
  dc_list.cal_VDes = cal_VDes;
  dc_list.cal_dVDes = cal_dVDes;

  // error values
  dc_list.erB = erB;
  dc_list.evB = evB;
  dc_list.eoB = eoB;
  dc_list.ewB = ewB;

  dc_list.erC = erC;
  dc_list.evC = evC;

  dc_list.cal_Ep = cal_Ep;
  dc_list.cal_Ev = cal_Ev;

  dc_list.cal_FErr = Bc_k*cal_FcMBarRef - cal_F;

  dc_list.dpRef = dpRef;
  dc_list.dlRef = dlCRef;
  // dc_list.dlRef = dlBRef;

  // dc_list.cal_FBarRef = Bc_k*cal_FcBarRef;
  dc_list.cal_FBarRef = Bc_k*cal_FcMBarRef;

  dc_list.tau = tau;

  dc_list.pCRB = model.hoap2.all.m*cal_VM.head(3);
  dc_list.lCRB = IC*cal_VM.tail(3);

  dc_list.pCth = Vector3d::Zero();
  dc_list.lCth = HC*model.hoap2.all.dth;

  dc_list.p = model.hoap2.all.m*cal_VM.head(3);
  dc_list.lC = IC*cal_VM.tail(3) + HC*model.hoap2.all.dth;
}
