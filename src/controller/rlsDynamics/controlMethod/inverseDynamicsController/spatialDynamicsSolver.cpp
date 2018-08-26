/**
   @author Sho Miyahara 2017

   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::spatialDynamicsSolver(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  // if(!info.sim.state)
  //   return tau;

  int n = info.dof.all + info.contact.c.all;

  MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  MatrixXd G = MatrixXd::Identity(n, n);
  // no motion
  // G <<
  //   cal_AB.transpose()*Wdh*cal_AB + Wq, MatrixXd::Zero(info.dof.all,info.contact.c.all),
  //   MatrixXd::Zero(info.contact.c.all,info.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // G <<
  //   cal_AB.transpose()*Wh*cal_AB + Jm.transpose()*Bm.transpose()*Wm*Bm*Jm + Wq, MatrixXd::Zero(info.dof.all,info.contact.c.all),
  //   MatrixXd::Zero(info.contact.c.all,info.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // centroidal
  G <<
    cal_AM.transpose()*Wdh*cal_AM + Wq, MatrixXd::Zero(info.dof.all,info.contact.c.all),
    MatrixXd::Zero(info.contact.c.all,info.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // momentum control
  (this->*momentumController_ptr)(info);

  // VectorXd rpkDes = VectorXd::Zero(2*info.contact.num);
  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  // VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;

  // centroidal
  VectorXd dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJmM*dqM;

  // nomotion
  VectorXd g = VectorXd::Zero(n);
  // g.transpose() <<
  //   -(cal_dLBRef - cal_CB).transpose()*Wdh*cal_AB,
  //   -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // VectorXd g = VectorXd::Zero(n);
  // g.transpose() <<
  //   -(cal_dLBRef - cal_CB).transpose()*Wdh*cal_AB - dVmBarRef.transpose()*Bm.transpose()*Wm*Bm*Jm,
  //   -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // // centroidal
  g.transpose() <<
    -(cal_dLCRef - cal_CM).transpose()*Wdh*cal_AM,
    -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  // **********************************************************************
  // int ceNum = 6;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  // CE <<
  //   cal_AB, -cal_Pc;

  // VectorXd ce = -(cal_CB + cal_GB);

  // // **********************************************************************
  // int ceNum = 6;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  // CE <<
  //   cal_AM, -cal_PcM;

  // VectorXd ce = -(cal_CM + cal_GC);

  // // **********************************************************************
  // int ceNum = 6 + info.contact.c.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  // CE <<
  //   cal_AB, -cal_Pc,
  //   Jc, MatrixXd::Zero(info.contact.c.all, info.contact.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CB + cal_GB),
  //   -dJc*dq;

  // // **********************************************************************
  // int ceNum = 6 + info.contact.c.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  // CE <<
  //   cal_AM, -cal_PcM,
  //   JcM, MatrixXd::Zero(info.contact.c.all, info.contact.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CM + cal_GC),
  //   -dJcM*dqM;

  // // **********************************************************************
  // int ceNum = 6 + info.contact.c.all + info.contact.m.all;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  // CE <<
  //   cal_AB, -cal_Pc,
  //   Jc, MatrixXd::Zero(info.contact.c.all, info.contact.c.all),
  //   Jm, MatrixXd::Zero(info.contact.m.all, info.contact.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CB + cal_GB),
  //   -dJc*dq,
  //   dVmBarRef - dJm*dq;

  // // **********************************************************************
  // MatrixXd J = MatrixXd::Zero(6*info.value.joint, info.dof.all); J
  // << TB2k, cal_J; MatrixXd dJ = MatrixXd::Zero(6*info.value.joint,
  // info.dof.all); dJ << dTB2k, cal_dJ;

  // int ceNum = 6 + 6*info.value.joint;
  // MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  // CE <<
  //   cal_AB, -cal_Pc,
  //   J, MatrixXd::Zero(6*info.value.joint, info.contact.c.all);

  // VectorXd ce = VectorXd::Zero(ceNum);
  // ce <<
  //   -(cal_CB + cal_GB),
  //   cal_dVRef - dJ*dq;
  // // **********************************************************************

  // centroidal
  // **********************************************************************
  int ceNum = 6 + info.contact.c.all + info.contact.m.all;
  MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  CE <<
    cal_AM, -cal_PcM,
    JcM, MatrixXd::Zero(info.contact.c.all, info.contact.c.all),
    JmM, MatrixXd::Zero(info.contact.m.all, info.contact.c.all);

  VectorXd ce = VectorXd::Zero(ceNum);
  ce <<
    -(cal_CM + cal_GC),
    -dJcM*dqM,
    dVmBarRef;
  // **********************************************************************

  VectorXd x = VectorXd::Zero(n);
  QuadProgpp::solver(G, g, "e", CE, ce, x);

  // ddqBRef = x.head(info.dof.all);
  ddqMRef = x.head(info.dof.all);
  cal_FcBarRef = x.tail(info.contact.c.all);
  // cal_FcBarRef = pInv(cal_Pc)*(cal_dLBRef + cal_GB);

  // torque control
  (this->*torqueController_ptr)(info);

  return tau;
}
