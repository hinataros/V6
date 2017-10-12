#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::outputConfig(Config &config)
{
  if(config.flag.debug) DEBUG;

  dc_list.rBDes = rBDes;
  dc_list.vBDes = vBDes;
  dc_list.dvBDes = dvBDes;

  dc_list.xiBDes = xiBDes;
  dc_list.wBDes = wBDes;
  dc_list.dwBDes = dwBDes;

  dc_list.cal_XDes = cal_XDes;
  dc_list.cal_VDes = cal_VDes;
  dc_list.cal_dVDes = cal_dVDes;

  dc_list.erB = erB;
  dc_list.evB = evB;
  dc_list.eoB = eoB;
  dc_list.ewB = ewB;

  dc_list.erC = erC;
  dc_list.evC = evC;
}
