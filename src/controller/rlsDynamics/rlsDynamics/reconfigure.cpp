/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::reconfigure()
{
  if(debug) DEBUG;

  // operational space reference
  cal_VcBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_VmBarRef = VectorXd::Zero(info.constraint->m.all);

  cal_VcBBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_VmBBarRef = VectorXd::Zero(info.constraint->m.all);
  cal_VcMBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_VmMBarRef = VectorXd::Zero(info.constraint->m.all);

  cal_dVcBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_dVmBarRef = VectorXd::Zero(info.constraint->m.all);

  cal_dVcBBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_dVmBBarRef = VectorXd::Zero(info.constraint->m.all);
  cal_dVcMBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_dVmMBarRef = VectorXd::Zero(info.constraint->m.all);
  cal_dVcCBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_dVmCBarRef = VectorXd::Zero(info.constraint->m.all);

  // force
  cal_FcaBarRef = VectorXd::Zero(info.constraint->c.all);
  cal_FcBarRef = VectorXd::Zero(info.constraint->c.all);
}
