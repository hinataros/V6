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

VectorXd RLS::RlsDynamics::dlrSolver(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  int n = info.dof.all + info.contact.c.all;

  // MatrixXd AM =
  //   (MatrixXd(info.dof.all-3)<<cal_AM.block(0,0,3,3), cal_AM.block(0,6,3,info.dof.joint)).finished();

  MatrixXd Wq = MatrixXd::Zero(info.dof.all,info.dof.all);
  // Wq.block(0,0,3,3) = Matrix3d::Zero();
  // Wq.block(0,0,3,3) = Matrix3d::Identity();
  Wq.block(3,3,3,3) = Matrix3d::Identity();
  Wq.block(6,6,info.dof.joint,info.dof.joint) = Wth;

  MatrixXd G = (MatrixXd(n, n) <<
                cal_AM.transpose()*WFSD*cal_AM + Wq, MatrixXd::Zero(info.dof.all,info.contact.c.all),
                MatrixXd::Zero(info.contact.c.all,info.dof.all), Bc.transpose()*WF*Bc + Pc.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();

  // momentum control
  (this->*momentumController_ptr)(config, info, model);

  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  VectorXd g = (VectorXd(n).transpose() <<
                -(cal_dLCRef - cal_CM).transpose()*Wb*cal_AM,
                -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();

  int ceNum = 6 + 3 + info.contact.c.all + info.contact.m.all;
  MatrixXd CE = (MatrixXd(ceNum, n) <<
                 cal_AM, -cal_PcM,
                 // cal_AM.block(0,0,3,info.dof.all), -cal_PcM.block(0,0,3,info.contact.c.all),
                 Matrix3d::Zero(), Matrix3d::Identity(), MatrixXd::Zero(3,info.dof.joint+info.contact.c.all),
                 JcM, MatrixXd::Zero(info.contact.c.all, info.contact.c.all),
                 JmM, MatrixXd::Zero(info.contact.m.all, info.contact.c.all)).finished();

  VectorXd ce = (VectorXd(ceNum) <<
                 // -(cal_CM + cal_GC).head(3),
                 -(cal_CM + cal_GC),
                 dwBRef,
                 -dJcM*dqM,
                 Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJmM*dqM).finished();

  VectorXd x = VectorXd::Zero(n);

  // if(info.contact.c.all==12){
  //   MatrixXd CI = (MatrixXd(n, n) <<
  //                  MatrixXd::Zero(info.dof.all, info.dof.all), MatrixXd::Zero(info.dof.all, info.contact.c.all),
  //                  MatrixXd::Zero(info.contact.c.all, info.dof.all), Bc.transpose()*WFmin*Bc).finished();

  //   VectorXd ci = (VectorXd(n) <<
  //                  VectorXd::Zero(info.dof.all), 0.,0.,2.e-0,0.,0.,0., 0.,0.,2.e-0,0.,0.,0.).finished();
  //   QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
  // }

  // else
    QuadProgpp::solver(G, g, "e", CE, ce, x);

  ddqMoptRef = x.head(info.dof.all);
  cal_FcBarRef = x.tail(info.contact.c.all);

  // torque control
  (this->*torqueController_ptr)(config, info, model);


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
