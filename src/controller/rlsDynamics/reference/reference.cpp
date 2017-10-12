#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  comReference(config, info, model, t);
  baseReference(config, info, model, t);
  endEffectorReference(config, info, model, t);

  cal_dVBRef <<
    dvBRef,
    dwBRef;

  cal_dVMRef <<
    dvCRef,
    dwBRef;
}
