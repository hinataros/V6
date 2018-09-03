/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::mixedGeneralizedMomentum(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  MatrixXd ACBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
  ACBar <<
    cal_AM,
    JcM;

  MatrixXd dACBar = MatrixXd::Zero(6+info.contact.c.all, info.dof.all);
  dACBar <<
    cal_dAM,
    dJcM;

  VectorXd cal_dLCBarRef = VectorXd::Zero(6+info.contact.c.all);
  cal_dLCBarRef.head(6) = cal_dLCRef;

  VectorXd ddqLCRef = pInv(ACBar)*(cal_dLCBarRef - dACBar*dqM);

  MatrixXd JmMBar = JmM*N(ACBar);

  VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
  VectorXd dVmTildeRef = dVmBarRef - dJmM*dqM - JmM*ddqLCRef;

  VectorXd ddqmRef = N(ACBar)*pInv(JmMBar)*dVmTildeRef;

  // ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqthD(info);
  ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqthinit(info);

  return ddqMoptRef;
}
