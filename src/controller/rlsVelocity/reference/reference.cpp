#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsVelocity.hpp"

void RLS::RlsVelocity::reference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  comReference(config, info, model, t);
  baseReference(config, info, model, t);

  endEffectorReference(config, info, model, t);

  cal_VBRef <<
    vBRef,
    wBRef;

  cal_VMRef <<
    vCRef,
    wBRef;
}
