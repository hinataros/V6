/**
   @author Sho Miyahara 2018

   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::spatialDynamicsSolver()
{
  if(debug) DEBUG;

  // if(!info.sim.state)
  //   return tau;

  int n = info.model.dof.all + info.constraint.c.all;

  MatrixXd Wq = MatrixXd::Zero(info.model.dof.all,info.model.dof.all);
  Wq.block(6,6,info.model.dof.joint,info.model.dof.joint) = Wth;

  MatrixXd G = MatrixXd::Identity(n, n);
  // no motion
  // G <<
  //   model->cal_AB.transpose()*Wdh*model->cal_AB + Wq, MatrixXd::Zero(info.model.dof.all,info.constraint.c.all),
  //   MatrixXd::Zero(info.constraint.c.all,info.model.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // G <<
  //   model->cal_AB.transpose()*Wh*model->cal_AB + Jm.transpose()*Bm.transpose()*Wm*Bm*Jm + Wq, MatrixXd::Zero(info.model.dof.all,info.constraint.c.all),
  //   MatrixXd::Zero(info.constraint.c.all,info.model.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // centroidal
  G <<
    model->cal_AM.transpose()*Wdh*model->cal_AM + Wq, MatrixXd::Zero(info.model.dof.all,info.constraint.c.all),
    MatrixXd::Zero(info.constraint.c.all,info.model.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // momentum control
  (this->*momentumController_ptr)();
  (this->*operationalSpaceController_ptr)();

  // VectorXd rpkDes = VectorXd::Zero(2*info.constraint.num);
  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  // VectorXd dVmBarRef = cal_dVmBarRef + dBm.transpose()*model->cal_V;

  // centroidal
  VectorXd dVmBarRef = cal_dVmBarRef + dBm.transpose()*model->cal_V - dJmM*model->dqM;

  // nomotion
  VectorXd g = VectorXd::Zero(n);
  // g.transpose() <<
  //   -(cal_dLBRef - model->cal_CB).transpose()*Wdh*model->cal_AB,
  //   -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // VectorXd g = VectorXd::Zero(n);
  // g.transpose() <<
  //   -(cal_dLBRef - model->cal_CB).transpose()*Wdh*model->cal_AB - dVmBarRef.transpose()*Bm.transpose()*Wm*Bm*Jm,
  //   -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // // centroidal
  g.transpose() <<
    -(cal_dLCRef - model->cal_CM).transpose()*Wdh*model->cal_AM,
    -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // **********************************************************************
  // int ceNum = 6;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  // CE <<
  //   model->cal_AB, -cal_Pc;

  // VectorXd ce = -(cal_CB + model->cal_GB);

  // // **********************************************************************
  // int ceNum = 6;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  // CE <<
  //   model->cal_AM, -cal_PcM;

  // VectorXd ce = -(cal_CM + model->cal_GC);

  // // **********************************************************************
  // int ceNum = 6 + info.constraint.c.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  // CE <<
  //   model->cal_AB, -cal_Pc,
  //   Jc, MatrixXd::Zero(info.constraint.c.all, info.constraint.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CB + model->cal_GB),
  //   -dJc*model->dq;

  // // **********************************************************************
  // int ceNum = 6 + info.constraint.c.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  // CE <<
  //   model->cal_AM, -cal_PcM,
  //   JcM, MatrixXd::Zero(info.constraint.c.all, info.constraint.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CM + model->cal_GC),
  //   -dJcM*model->dqM;

  // // **********************************************************************
  // int ceNum = 6 + info.constraint.c.all + info.constraint.m.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  // CE <<
  //   model->cal_AB, -cal_Pc,
  //   Jc, MatrixXd::Zero(info.constraint.c.all, info.constraint.c.all),
  //   Jm, MatrixXd::Zero(info.constraint.m.all, info.constraint.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CB + model->cal_GB),
  //   -dJc*model->dq,
  //   dVmBarRef - dJm*model->dq;

  // // **********************************************************************
  // MatrixXd J = MatrixXd::Zero(6*info.value.joint, info.model.dof.all); J
  // << TB2k, cal_J; MatrixXd dJ = MatrixXd::Zero(6*info.value.joint,
  // info.model.dof.all); dJ << dTB2k, cal_dJ;

  // int ceNum = 6 + 6*info.value.joint;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  // CE <<
  //   model->cal_AB, -cal_Pc,
  //   J, MatrixXd::Zero(6*info.value.joint, info.constraint.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CB + model->cal_GB),
  //   cal_dVRef - dJ*model->dq;
  // // **********************************************************************

  // centroidal
  // **********************************************************************
  int ceNum = 6 + info.constraint.c.all + info.constraint.m.all;
  MatrixXd CE = MatrixXd::Zero(ceNum,info.model.dof.all+info.constraint.c.all);
  CE <<
    model->cal_AM, -cal_PcM,
    JcM, MatrixXd::Zero(info.constraint.c.all, info.constraint.c.all),
    JmM, MatrixXd::Zero(info.constraint.m.all, info.constraint.c.all);

  VectorXd ce = VectorXd::Zero(ceNum);
  ce <<
    -(model->cal_CM + model->cal_GC),
    -dJcM*model->dqM,
    dVmBarRef;
  // **********************************************************************

  VectorXd x = VectorXd::Zero(n);
  QuadProgpp::solver(G, g, "e", CE, ce, x);

  // ddqBRef = x.head(info.model.dof.all);
  ddqMRef = x.head(info.model.dof.all);
  cal_FcBarRef = x.tail(info.constraint.c.all);
  // cal_FcBarRef = pInv(cal_Pc)*(cal_dLBRef + model->cal_GB);

  // torque control
  (this->*torqueController_ptr)();

  return tau;
}
