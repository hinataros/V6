/**
   @author Sho Miyahara 2017

   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::dlrSolver(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  int n = info.dof.all + info.contact.c.all;

  MatrixXd cdh = cal_AM.transpose()*Wdh*cal_AM;

  MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  // Wq.block(0,0,3,3) = Matrix3d::Zero();
  // Wq.block(0,0,3,3) = Matrix3d::Identity();
  Wq.block(3,3,3,3) = Wth(0,0)*Matrix3d::Identity();
  Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  MatrixXd cddq = Wq;

  MatrixXd cdvm = JmM.transpose()*Bm.transpose()*Wm*Bm*JmM;

  MatrixXd JdwB = MatrixXd::Zero(3,info.dof.all);
  JdwB.block(0,3,3,3) = Matrix3d::Identity();

  MatrixXd cdwB = JdwB.transpose()*0.1*Wm.block(0,0,3,3)*JdwB;

  MatrixXd cp = Pc.transpose()*Bp.transpose()*Wp*Bp*Pc;
  MatrixXd cFcBar = Bc.transpose()*WF*Bc;

  MatrixXd cdv = cdh + cddq + cdvm + cdwB;
  MatrixXd cF = cp + cFcBar;

  // minimize
  MatrixXd G = MatrixXd::Zero(n, n);
  G.block(0,0, info.dof.all, info.dof.all) = cdv;
  G.block(info.dof.all, info.dof.all, info.contact.c.all, info.contact.c.all) = cF;

  // momentum control
  (this->*momentumController_ptr)(info);

  VectorXd dhRef = cal_dLCRef - cal_CM;
  VectorXd gdv = -(dhRef.transpose()*Wdh*cal_AM).transpose();

  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  VectorXd gF = (-rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc).transpose();

  VectorXd dvmRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJmM*dqM;
  VectorXd gdvm = -(dvmRef.transpose()*Bm.transpose()*Wm*Bm*JmM).transpose();

  VectorXd gdwB = -(dwBRef.transpose()*0.1*Wm.block(0,0,3,3)*JdwB).transpose();

  // minimize
  VectorXd g = VectorXd::Zero(n);
  g <<
    gdv + gdvm + gdwB,
    gF;

  // subject to
  int ceNum = 6 + info.contact.c.all;
  // int ceNum = 6 + info.contact.c.all + info.contact.m.all;

  MatrixXd CE = MatrixXd::Zero(ceNum, n);
  CE.block(0,0,6,n) << cal_AM, -cal_PcM;
  CE.block(6,0,info.contact.c.all, info.dof.all) = JcM;
  // CE.block(6+info.contact.c.all,0,info.contact.m.all, info.dof.all) = JmM;

  VectorXd cal_dVmBarRef = Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V;
  VectorXd ce = VectorXd::Zero(ceNum);
  ce <<
    -(cal_CM + cal_GC),
    -dJcM*dqM;
  // ce.segment(6+info.contact.c.all, info.contact.m.all) = cal_dVmBarRef - dJmM*dqM;

  int ciNum = 2*info.dof.joint;
  MatrixXd CI = MatrixXd::Zero(ciNum, n);
  MatrixXd Smin = MatrixXd::Zero(info.dof.joint,info.dof.joint);
  MatrixXd Smax = MatrixXd::Zero(info.dof.joint,info.dof.joint);

  Smin = diag(info.dof.joint,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,
              0.,0.,0.,1.
              );
  Smax = diag(info.dof.joint,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,
              0.,0.,0.,1.
              );

  CI.block(0,6,info.dof.joint,info.dof.joint) = Smin;
  CI.block(info.dof.joint,6,info.dof.joint,info.dof.joint) = -Smax;

  VectorXd thmin = VectorXd::Zero(info.dof.joint);
  VectorXd thmax = VectorXd::Zero(info.dof.joint);

  thmin <<
    0.,0.,0.,0.,0.,0.,
    0.,0.,0.,0.,0.,0.,
    0.,0.,0.,-115.,
    0.,0.,0.,-115.;

  thmax <<
    0.,0.,0.,129.,0.,0.,
    0.,0.,0.,129.,0.,0.,
    0.,0.,0.,0.,
    0.,0.,0.,0.;

  VectorXd ci = VectorXd::Zero(ciNum);
  ci <<
    Smin*(1/dt*dt)*(DEG2RAD*thmin - (th + dt*dth)),
    -Smax(1/dt*dt)*(DEG2RAD*thmax - (th + dt*dth));

  VectorXd x = VectorXd::Zero(n);
  if(info.contact.c.all==12){
    MatrixXd CI = (MatrixXd(n, n) <<
                   MatrixXd::Zero(info.dof.all, info.dof.all), MatrixXd::Zero(info.dof.all, info.contact.c.all),
                   MatrixXd::Zero(info.contact.c.all, info.dof.all), Bc.transpose()*WFmin*Bc).finished();

    VectorXd ci = (VectorXd(n) <<
                   VectorXd::Zero(info.dof.all), 0.,0.,2.e-0,0.,0.,0., 0.,0.,2.e-0,0.,0.,0.).finished();
    QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
  }

  // else
  QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
    // QuadProgpp::solver(G, g, "e", CE, ce, x);

  ddqMoptRef = x.head(info.dof.all);
  cal_FcBarRef = x.tail(info.contact.c.all);

  // torque control
  (this->*torqueController_ptr)(info);


  // int n = info.dof.all + info.contact.c.all;

  // MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  // Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  // MatrixXd G = (MatrixXd(n, n) <<
  //               cal_AM.transpose()*WFSD*cal_AM + Wq, MatrixXd::Zero(info.dof.all,info.contact.c.all),
  //               MatrixXd::Zero(info.contact.c.all,info.dof.all), Bc.transpose()*WF*Bc + Pc.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();

  // // momentum control
  // (this->*momentumController_ptr)(config, info, model);

  // VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  // VectorXd g = (VectorXd(n).transpose() <<
  //               -(cal_dLCRef - cal_CM).transpose()*WFSD*cal_AM,
  //               -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();
  // int ceNum = 6 + info.contact.c.all + info.contact.m.all;
  // MatrixXd CE = (MatrixXd(ceNum, n) <<
  //                cal_AM, -cal_PcM,
  //                JcM, MatrixXd::Zero(info.contact.c.all, info.contact.c.all),
  //                JmM, MatrixXd::Zero(info.contact.m.all, info.contact.c.all)).finished();

  // VectorXd ce = (VectorXd(ceNum) <<
  //                -(cal_CM + cal_GC),
  //                -dJcM*dqM,
  //                Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJmM*dqM).finished();

  // VectorXd x = VectorXd::Zero(n);

  // if(info.contact.c.all==12){
  //   MatrixXd CI = (MatrixXd(n, n) <<
  //                  MatrixXd::Zero(info.dof.all, info.dof.all), MatrixXd::Zero(info.dof.all, info.contact.c.all),
  //                  MatrixXd::Zero(info.contact.c.all, info.dof.all), Bc.transpose()*WFmin*Bc).finished();

  //   VectorXd ci = (VectorXd(n) <<
  //                  VectorXd::Zero(info.dof.all), 0.,0.,1.e-0,0.,0.,0., 0.,0.,1.e-0,0.,0.,0.).finished();
  //   QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
  // }

  // else
  //   QuadProgpp::solver(G, g, "e", CE, ce, x);

  // ddqMoptRef = x.head(info.dof.all);
  // cal_FcBarRef = x.tail(info.contact.c.all);

  // // torque control
  // (this->*torqueController_ptr)(config, info, model);

  return tau;
}
