#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reference(Config &config, Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  comReference(config, info, model, t);
  baseReference(config, info, model, t);

  cal_VBRef <<
    vBRef,
    wBRef;
  cal_VMRef <<
    vCRef,
    wBRef;

  cal_dVBRef <<
    dvBRef,
    dwBRef;
  cal_dVMRef <<
    dvCRef,
    dwBRef;
  cal_dVCRef <<
    dvCRef,
    IC.inverse()*(-KDlC*model.hoap2.all.lC - dIC*(cal_VM.tail(3) + IC.inverse()*HC*model.hoap2.all.dth));

  endEffectorReference(config, info, model, t);
}
