/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::baseOrientationSequence(Config &config,Info &info, Model &model, double &t)
{
  if(config.flag.debug) DEBUG;

  for(int i=0; i<3; i++){
    des = makeSpline5(t-info.sim.tw0, info.sim.twf, xiBpreDes(i), xiBf(i));
    xiBDes(i) = des(0) + xiB0(i);
    dxiBDes(i) = des(1);
    ddxiBDes(i) = des(2);
  }

  // smiyahara: オイラー表現の姿勢は計算しといたほうがいいのでは
  RBDes = xi2R(xiBDes);
  wBDes = dxi2w(dxiBDes, R2xi(model.hoap2.limb[0].node[0].R));
  dwBDes = ddxi2dw(ddxiBDes, R2xi(model.hoap2.limb[0].node[0].R), w2dxi(model.hoap2.limb[0].node[0].w, R2xi(model.hoap2.limb[0].node[0].R)));

  eoB = 0.5*(cross(model.hoap2.limb[0].node[0].R.col(0))*RBDes.col(0)
             + cross(model.hoap2.limb[0].node[0].R.col(1))*RBDes.col(1)
             + cross(model.hoap2.limb[0].node[0].R.col(2))*RBDes.col(2));
  ewB = wBDes - model.hoap2.limb[0].node[0].w;

  // velocityController
  wBRef = wBDes + KpwB*eoB;

  dwBRef = dwBDes + KdwB*ewB + KpwB*eoB;

  VectorXd rpkDes = VectorXd::Zero(2*BpDiag.diagonal().sum()/2);
  MatrixXd G = (MatrixXd(3+info.contact.c.all,3+info.contact.c.all)<<
                 MatrixXd::Identity(3,3), MatrixXd::Zero(3,info.contact.c.all),
                 MatrixXd::Zero(3,info.contact.c.all).transpose(), Bc.transpose()*WF*Bc + Pc.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();

  VectorXd g = (VectorXd(3+info.contact.c.all).transpose()<<
                Vector3d::Zero().transpose(),-rpkDes.transpose()*Bp.transpose()*Wp*Bp*Pc).finished();

  MatrixXd CE = (MatrixXd(3,3+info.contact.c.all)<<
                  IC, -cal_PcM.block(3,0,3,info.contact.c.all)).finished();
  VectorXd ce = dIC*cal_VM.tail(3);

  VectorXd x = VectorXd::Zero(3+info.contact.c.all);

  QuadProgpp::solver(G, g, "e", CE, ce, x);

  dwBRef = x.head(3) + KdwB*ewB;
}
