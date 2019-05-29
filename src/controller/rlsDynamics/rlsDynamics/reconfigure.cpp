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

  // amiyata
  wBcD = BwB_Diag.diagonal().sum();
  pcD = BLC_Diag.block(0,0, 3,3).diagonal().sum();
  lCcD = BLC_Diag.block(3,3, 3,3).diagonal().sum();

  BwB = MatrixXd::Zero(3, wBcD);
  BLC = MatrixXd::Zero(6, pcD+lCcD);
  BLCAut = MatrixXd::Zero(6, 6-(pcD+lCcD)); // authogonal basis matrix
  for(int i=0, si=0; i<3; i++){
    if(BwB_Diag(i, i)){
      BwB(i,si) = 1.;
      si++;
    }
  }
  for(int i=0, si=0, sni=0; i<6; i++){
    if(BLC_Diag(i, i)){
      BLC(i,si) = 1.;
      si++;
    } else {
      BLCAut(i, sni) = 1.;
      sni++;
    }
  }
  wCcD = BwC_Diag.diagonal().sum(); // 2019/04/09
  BwC = MatrixXd::Zero(3, wCcD);
  BwCAut = MatrixXd::Zero(3, 3-  wCcD);
  for(int i=0, si=0, sni=0; i<3; i++){
    if(BwC_Diag(i, i)){
      BwC(i,si) = 1.;
      si++;
    } else {
      BwCAut(i, sni) = 1.;
      sni++;
    }
  }
}
