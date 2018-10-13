/**
   @author Sho Miyahara 2018
*/

#include "_ext.hpp"

VectorXd RLS::EXT::testMotionControler(RlsDynamics &io)
{
  if(debug) DEBUG;

  o(io.JcM);
  o(io.model->cal_AM);
  gc;

  // (this->*operationalSpaceController_ptr)();

  // MatrixXd ACBar = MatrixXd::Zero(6+info.constraint.c.all, info.model.dof.all);
  // ACBar <<
  //   model->cal_AM,
  //   JcM;

  // MatrixXd dACBar = MatrixXd::Zero(6+info.constraint.c.all, info.model.dof.all);
  // dACBar <<
  //   model->cal_dAM,
  //   dJcM;

  // VectorXd cal_dLCBarRef = VectorXd::Zero(6+info.constraint.c.all);
  // cal_dLCBarRef.head(6) = cal_dLCRef;

  // VectorXd ddqLCRef = pInv(ACBar)*(cal_dLCBarRef - dACBar*model->dqM);

  // MatrixXd JmMBar = JmM*N(ACBar);

  // VectorXd dVmBarRef = cal_dVmBarRef + dBm.transpose()*model->cal_V;
  // VectorXd dVmTildeRef = dVmBarRef - dJmM*model->dqM - JmM*ddqLCRef;

  // VectorXd ddqmRef = N(ACBar)*pInv(JmMBar)*dVmTildeRef;

  // // ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqthD();
  // ddqMoptRef = ddqLCRef + ddqmRef + N(ACBar)*N(JmMBar)*ddqthinit();

  return ddqMoptRef;
}
