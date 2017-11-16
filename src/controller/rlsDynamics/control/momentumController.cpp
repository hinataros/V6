#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::momentumController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  dpRef = model.all.m*dvCRef;

  dlBRef =
    - model.all.m*cross(rB2C).transpose()*dvCRef + IC*dwBRef
    - model.all.m*cross(drB2C).transpose()*cal_VM.head(3) + dIC*cal_VM.tail(3);

  dlCRef = IC*dwBRef + dIC*model.limb[0].node[0].w;

  cal_dLBRef <<
    dpRef,
    dlBRef;

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
