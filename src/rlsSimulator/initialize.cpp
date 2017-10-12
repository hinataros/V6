#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::initialize(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  rB = Vector3d::Zero();
  RB = Matrix3d::Zero();
  voB = Vector3d::Zero();
  wB = Vector3d::Zero();
  th = VectorXd::Zero(info.dof.joint);
  dth = VectorXd::Zero(info.dof.joint);

  u = VectorXd::Zero(info.dof.joint);

  dvoB = dwB = Vector3d::Zero();
  ddth = VectorXd::Zero(info.dof.joint);

  for(int i=0; i<4; i++){
    k.vo[i] = k.w[i] = k.dvo[i] = k.dw[i] = Vector3d::Zero();
    k.dth[i] = k.ddth[i] = VectorXd::Zero(info.dof.joint);
  }
}
