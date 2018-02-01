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

  int n = info.dof.all + c;
  VectorXd x = VectorXd::Zero(n);

  MatrixXd G = MatrixXd::Identity(n, n);
  VectorXd g = VectorXd::Zero(n);

  Matrix6d Ch = Matrix6d::Identity();
  Ch *= 1.e-3;
  MatrixXd CJ = MatrixXd::Identity(6*info.value.joint, 6*info.value.joint);
  // CJ *= 1.e-3;

  int contact = 2;
  for(int i=0; i<contact; i++){
    if(cal_F(6*i+2)==0.)
      return tau;
  }

  MatrixXd Cp = MatrixXd::Identity(2*contact, 2*contact);
  // Cp *= 1.e-4;
  MatrixXd Cr = MatrixXd::Identity(c,c);
  Cr *= 1.e-4;

  MatrixXd J = MatrixXd::Zero(TB2k.rows(), TB2k.cols()+cal_J.cols());
  J <<
    TB2k, cal_J;

  MatrixXd Fz = MatrixXd::Identity(2*contact, 2*contact);
  MatrixXd S = MatrixXd::Zero(2,2);
  MatrixXd cal_S = MatrixXd::Zero(2*contact,6*contact);

  S <<
    0, -1,
    1, 0;
  for(int i=0; i<contact; i++){
    Fz.block(2*i,2*i,2,2) *= cal_F(6*i+2);
    cal_S.block(2*i,6*i+3,2,2) = S;
  }

  MatrixXd Pc = Fz.inverse()*cal_S;

  G.block(0,0,info.dof.all,info.dof.all) = cal_AB.transpose()*Ch*cal_AB + J.transpose()*CJ*J;
  G.block(info.dof.all,info.dof.all,c,c) = Pc.transpose()*Cp*Pc + Cr;

  VectorXd rpDes = VectorXd::Zero(2*contact);
  // VectorXd rpDes = rpk.head(4);
  // rpDes <<
  //   1.849940e-3,
  //   -3.892652e-2,
  //   1.913260e-3,
  //   3.895806e-2;

  g.transpose() <<
    -((cal_dLBRef - cal_CB).transpose()*cal_AB + cal_dVRef.transpose()*J), -rpDes.transpose()*Pc;

  int ceNum = 6;
  MatrixXd CE = MatrixXd::Zero(ceNum,info.dof.all+c);
  CE <<
    cal_AB, -TB2k.transpose()*Bc_k;

  VectorXd ce = -(cal_CB + cal_GB);

  QuadProgpp::solver(G, g, "e", CE, ce, x);

  ddqRef = x.head(info.dof.all);
  cal_FcBarRef = x.tail(c);

  // torque control
  (this->*torqueController_ptr)(config, info, model);

  return tau;
}
