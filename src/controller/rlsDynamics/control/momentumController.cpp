#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::momentumController(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  dpRef = model.all.m*dvCRef;

  dlBRef =
    model.all.m*cross(model.limb[0].node[0].r-model.all.rC).transpose()*dvCRef + IC*dwBRef
    + model.all.m*cross(model.limb[0].node[0].v-model.all.vC).transpose()*cal_VM.head(3) + dIC*cal_VM.tail(3);

  dlCRef = IC*dwBRef + cmM;
  // dlCRef = IC*dwBRef + HC*ddthRef + cmM;

  cal_dLBRef <<
    dpRef,
    dlBRef;

  cal_dLCRef <<
    dpRef,
    dlCRef;
}
