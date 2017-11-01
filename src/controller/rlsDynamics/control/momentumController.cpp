#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::momentumController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  // cal_dLBRef = Vector6d::Zero();

  cal_dLBRef <<
    model.all.m*dvCRef,
    IB*dwBRef;

  dpCRef = model.all.m*dvCRef;
  dlCRef = IB*dwBRef + HC*ddthRef + cmM;

  cal_dLCRef <<
    dpCRef,
    dlCRef;
}
