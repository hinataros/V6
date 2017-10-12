#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::velocityController(Config &config)
{
  if(config.flag.debug) DEBUG;

  cal_VcBarRef = -cal_Pc.transpose()*cal_VBRef;
  dthcRef = pInv(cal_Jc)*cal_VcBarRef;

  cal_VmBarRef = Bm.transpose()*cal_VRef - cal_Pm.transpose()*cal_VBRef;
  cal_VmTildeRef = cal_VmBarRef - cal_Jm*pInv(cal_Jc)*cal_VcBarRef;
  cal_JmBar = cal_Jm*N(cal_Jc);

  dthmRef = pInv(cal_JmBar)*cal_VmTildeRef;

  dthRef = dthcRef + dthmRef;

  // dqRef <<
  //   -pi(cal_Pc.transpose())*cal_Jc*dthRef,
  //   dthRef;

  dqRef <<
    cal_VBRef,
    dthRef;
}
