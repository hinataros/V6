/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::spatialReference(Model &model)
{
  if(debug) DEBUG;

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
  // cal_dVCRef <<
  //   dvCRef,
  //   IC.inverse()*(-KDlC*model.hoap2.all.lC - dIC*(cal_VM.tail(3) + IC.inverse()*HC*model.hoap2.all.dth));
}
