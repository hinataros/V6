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

void RLS::RlsDynamics::distributionSolver(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  int contact = 2;

  MatrixXd CF = MatrixXd::Identity(info.contact.c.all, info.contact.c.all);
  CF *= 1.e-6;
  MatrixXd Cp = MatrixXd::Identity(2*contact, 2*contact);

  bool solverFlag = true;
  for(int i=0; i<contact; i++){
    if(cal_F(6*i+2)==0.)
      solverFlag = false;
  }

  if(solverFlag){
    MatrixXd Fz = MatrixXd::Identity(2*contact, 2*contact);
    MatrixXd S = MatrixXd::Zero(2,2);
    MatrixXd cal_S = MatrixXd::Zero(2*contact,6*contact);

    VectorXd rpkDes = VectorXd::Zero(2*contact);

    S <<
      0, -1,
      1, 0;
    for(int i=0; i<contact; i++){
      Fz.block(2*i,2*i,2,2) *= cal_F(6*i+2);
      cal_S.block(2*i,6*i+3,2,2) = S;
    }

    MatrixXd Pc = Fz.inverse()*cal_S;

    MatrixXd G = Pc.transpose()*Cp*Pc + CF;
    VectorXd g = -rpkDes.transpose()*Cp*Pc;

    MatrixXd CE = cal_Pc;
    VectorXd ce = cal_dLBRef + cal_GB;

    QuadProgpp::solver(G, g, "e", CE, ce, cal_FcBarRef);
  }
}
