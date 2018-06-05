/**
   @author Sho Miyahara 2017

   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::atlasSolver(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(!info.sim.state)
    return tau;

  int n = info.dof.all + info.contact.c.all;

  MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  MatrixXd J = MatrixXd::Zero(TB2k.rows(), TB2k.cols()+cal_J.cols());
  J <<
    TB2k, cal_J;

  MatrixXd G = MatrixXd::Identity(n, n);
  G <<
    cal_AB.transpose()*WFSD*cal_AB + J.transpose()*WJ*J + Wq, MatrixXd::Zero(info.dof.all,info.contact.c.all),
    MatrixXd::Zero(info.contact.c.all,info.dof.all), Pc.transpose()*Bp.transpose()*Wp*Bp*Pc + Bc.transpose()*WF*Bc;

  // momentum control
  (this->*momentumController_ptr)(config, info, model);

  // VectorXd rpkDes = VectorXd::Zero(2*info.contact.num);
  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);

  VectorXd g = VectorXd::Zero(n);
  g.transpose() <<
    -(cal_dLBRef - cal_CB).transpose()*WFSD*cal_AB - cal_dVRef.transpose()*WJ*J,
    -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc;

  int ceNum = 6;
  MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+info.contact.c.all);
  CE <<
    cal_AB, -cal_Pc;

  VectorXd ce = -(cal_CB + cal_GB);

  VectorXd x = VectorXd::Zero(n);
  QuadProgpp::solver(G, g, "e", CE, ce, x);

  ddqBRef = x.head(info.dof.all);
  cal_FcBarRef = x.tail(info.contact.c.all);

  // torque control
  (this->*torqueController_ptr)(config, info, model);

  return tau;
}
