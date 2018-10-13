/**
   @author Sho Miyahara 2018

   1/2 x^T G x + g^T x
   CE x = ce
   CI x >= ci
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

VectorXd RLS::RlsDynamics::dlrSolver()
{
  if(debug) DEBUG;

  int n = info.model.dof.all + info.constraint.c.all;

  MatrixXd cdh = model->cal_AM.transpose()*Wdh*model->cal_AM;

  MatrixXd Wq = MatrixXd::Zero(info.model.dof.all,info.model.dof.all);
  // Wq.block(0,0,3,3) = Matrix3d::Zero();
  // Wq.block(0,0,3,3) = Matrix3d::Identity();
  Wq.block(3,3,3,3) = Wth(0,0)*Matrix3d::Identity();
  Wq.block(6,6,info.model.dof.joint,info.model.dof.joint) = Wth;

  MatrixXd cddq = Wq;

  MatrixXd cdvm = JmM.transpose()*Bm.transpose()*Wm*Bm*JmM;

  MatrixXd JdwB = MatrixXd::Zero(3,info.model.dof.all);
  JdwB.block(0,3,3,3) = Matrix3d::Identity();

  MatrixXd cdwB = JdwB.transpose()*0.1*Wm.block(0,0,3,3)*JdwB;

  MatrixXd cp = Pc.transpose()*Bp.transpose()*Wp*Bp*Pc;
  MatrixXd cFcBar = Bc.transpose()*WF*Bc;

  MatrixXd cdv = cdh + cddq + cdvm + cdwB;
  MatrixXd cF = cp + cFcBar;

  // minimize
  MatrixXd G = MatrixXd::Zero(n, n);
  G.block(0,0, info.model.dof.all, info.model.dof.all) = cdv;
  G.block(info.model.dof.all, info.model.dof.all, info.constraint.c.all, info.constraint.c.all) = cF;

  // momentum control
  (this->*momentumController_ptr)();
  (this->*operationalSpaceController_ptr)();

  VectorXd dhRef = cal_dLCRef - model->cal_CM;
  VectorXd gdv = -(dhRef.transpose()*Wdh*model->cal_AM).transpose();

  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  VectorXd gF = (-rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc).transpose();

  VectorXd dvmRef = cal_dVmBarRef + dBm.transpose()*model->cal_V - dJmM*model->dqM;
  VectorXd gdvm = -(dvmRef.transpose()*Bm.transpose()*Wm*Bm*JmM).transpose();

  VectorXd gdwB = -(fb.dwBfb.transpose()*0.1*Wm.block(0,0,3,3)*JdwB).transpose();

  // minimize
  VectorXd g = VectorXd::Zero(n);
  g <<
    gdv + gdvm + gdwB,
    gF;

  // subject to
  int ceNum = 6 + info.constraint.c.all;
  // int ceNum = 6 + info.constraint.c.all + info.constraint.m.all;

  MatrixXd CE = MatrixXd::Zero(ceNum, n);
  CE.block(0,0,6,n) << model->cal_AM, -cal_PcM;
  CE.block(6,0,info.constraint.c.all, info.model.dof.all) = JcM;
  // CE.block(6+info.constraint.c.all,0,info.constraint.m.all, info.model.dof.all) = JmM;

  VectorXd cal_dVmBarRef = cal_dVmBarRef + dBm.transpose()*model->cal_V;
  VectorXd ce = VectorXd::Zero(ceNum);
  ce <<
    -(model->cal_CM + model->cal_GC),
    -dJcM*model->dqM;
  // ce.segment(6+info.constraint.c.all, info.constraint.m.all) = cal_dVmBarRef - dJmM*dqM;

  int ciNum = 2*info.model.dof.joint;
  MatrixXd CI = MatrixXd::Zero(ciNum, n);
  MatrixXd Smin = MatrixXd::Zero(info.model.dof.joint,info.model.dof.joint);
  MatrixXd Smax = MatrixXd::Zero(info.model.dof.joint,info.model.dof.joint);

  Smin = diag(info.model.dof.joint,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,
              0.,0.,0.,1.
              );
  Smax = diag(info.model.dof.joint,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,0.,0.,
              0.,0.,0.,1.,
              0.,0.,0.,1.
              );

  CI.block(0,6,info.model.dof.joint,info.model.dof.joint) = Smin;
  CI.block(info.model.dof.joint,6,info.model.dof.joint,info.model.dof.joint) = -Smax;

  VectorXd thmin = VectorXd::Zero(info.model.dof.joint);
  VectorXd thmax = VectorXd::Zero(info.model.dof.joint);

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
    Smin*(1/worldModel->dt*worldModel->dt)*(DEG2RAD*thmin - (model->th + worldModel->dt*model->dth)),
    -Smax(1/worldModel->dt*worldModel->dt)*(DEG2RAD*thmax - (model->th + worldModel->dt*model->dth));

  VectorXd x = VectorXd::Zero(n);
  if(info.constraint.c.all==12){
    MatrixXd CI = (MatrixXd(n, n) <<
                   MatrixXd::Zero(info.model.dof.all, info.model.dof.all), MatrixXd::Zero(info.model.dof.all, info.constraint.c.all),
                   MatrixXd::Zero(info.constraint.c.all, info.model.dof.all), Bc.transpose()*WFmin*Bc).finished();

    VectorXd ci = (VectorXd(n) <<
                   VectorXd::Zero(info.model.dof.all), 0.,0.,2.e-0,0.,0.,0., 0.,0.,2.e-0,0.,0.,0.).finished();
    QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
  }

  // else
  QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
    // QuadProgpp::solver(G, g, "e", CE, ce, x);

  ddqMoptRef = x.head(info.model.dof.all);
  cal_FcBarRef = x.tail(info.constraint.c.all);

  // torque control
  (this->*torqueController_ptr)();


  // int n = info.model.dof.all + info.constraint.c.all;

  // MatrixXd Wq = MatrixXd::Zero(info.model.dof.all,info.model.dof.all);
  // Wq.block(6,6,info.model.dof.joint,info.model.dof.joint) = Wth;

  // MatrixXd G = (MatrixXd(n, n) <<
  //               model->cal_AM.transpose()*WFSD*model->cal_AM + Wq, MatrixXd::Zero(info.model.dof.all,info.constraint.c.all),
  //               MatrixXd::Zero(info.constraint.c.all,info.model.dof.all), Bc.transpose()*WF*Bc + Pc.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();

  // // momentum control
  // (this->*momentumController_ptr)(config, info, model);

  // VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  // VectorXd g = (VectorXd(n).transpose() <<
  //               -(cal_dLCRef - cal_CM).transpose()*WFSD*model->cal_AM,
  //               -rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();
  // int ceNum = 6 + info.constraint.c.all + info.constraint.m.all;
  // MatrixXd CE = (MatrixXd(ceNum, n) <<
  //                model->cal_AM, -cal_PcM,
  //                JcM, MatrixXd::Zero(info.constraint.c.all, info.constraint.c.all),
  //                JmM, MatrixXd::Zero(info.constraint.m.all, info.constraint.c.all)).finished();

  // VectorXd ce = (VectorXd(ceNum) <<
  //                -(cal_CM + cal_GC),
  //                -dJcM*dqM,
  //                Bm.transpose()*cal_dVRef + dBm.transpose()*cal_V - dJmM*dqM).finished();

  // VectorXd x = VectorXd::Zero(n);

  // if(info.constraint.c.all==12){
  //   MatrixXd CI = (MatrixXd(n, n) <<
  //                  MatrixXd::Zero(info.model.dof.all, info.model.dof.all), MatrixXd::Zero(info.model.dof.all, info.constraint.c.all),
  //                  MatrixXd::Zero(info.constraint.c.all, info.model.dof.all), Bc.transpose()*WFmin*Bc).finished();

  //   VectorXd ci = (VectorXd(n) <<
  //                  VectorXd::Zero(info.model.dof.all), 0.,0.,1.e-0,0.,0.,0., 0.,0.,1.e-0,0.,0.,0.).finished();
  //   QuadProgpp::solver(G, g, CE, ce, CI, ci, x);
  // }

  // else
  //   QuadProgpp::solver(G, g, "e", CE, ce, x);

  // ddqMoptRef = x.head(info.model.dof.all);
  // cal_FcBarRef = x.tail(info.constraint.c.all);

  // // torque control
  // (this->*torqueController_ptr)(config, info, model);

  return tau;
}
