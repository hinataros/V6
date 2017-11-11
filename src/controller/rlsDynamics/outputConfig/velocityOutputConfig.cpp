#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::velocityOutputConfig(Config &config, Model &model)
{
  if(config.flag.debug) DEBUG;

  // desired value
  vc_list.rBDes = rBDes;
  vc_list.vBDes = vBDes;

  vc_list.xiBDes = xiBDes;
  vc_list.wBDes = wBDes;

  vc_list.cal_XDes = cal_XDes;
  vc_list.cal_VDes = cal_VDes;

  // error value
  vc_list.erC = erC;
  vc_list.erB = erB;
  vc_list.eoB = eoB;

  vc_list.vBRef = vBRef;
  vc_list.wBRef = wBRef;
  vc_list.dthRef = dthRef;
}
