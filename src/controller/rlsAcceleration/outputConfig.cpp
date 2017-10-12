#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

void RLS::RlsAcceleration::outputConfig(Config &config)
{
  if(config.flag.debug) DEBUG;

  // desired value
  ac_list.rBDes = rBDes;
  ac_list.vBDes = vBDes;
  ac_list.dvBDes = dvBDes;

  ac_list.xiBDes = xiBDes;
  ac_list.wBDes = wBDes;
  ac_list.dwBDes = dwBDes;

  ac_list.cal_XDes = cal_XDes;
  ac_list.cal_VDes = cal_VDes;
  ac_list.cal_dVDes = cal_dVDes;

  // error value
  ac_list.erB = erB;
  ac_list.evB = evB;
  ac_list.eoB = eoB;
  ac_list.ewB = ewB;

  ac_list.dvBRef = dvBRef;
  ac_list.dwBRef = dwBRef;
  ac_list.ddthRef = ddthRef;
}
