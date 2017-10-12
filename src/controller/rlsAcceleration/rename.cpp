#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsAcceleration.hpp"

void RLS::RlsAcceleration::rename(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  cal_VB <<
    model.limb[0].node[0].v,
    model.limb[0].node[0].w;
}
