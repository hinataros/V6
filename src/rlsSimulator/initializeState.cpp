/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::initializeState(const Info &info)
{
  if(debug) DEBUG;

  state = new State[info.treeModelNum];

  u = new VectorXd[info.treeModelNum];

  k = new K[info.treeModelNum];

  this->config.controlInput = new string[info.treeModelNum];

  // dvoB = dwB = Vector3d::Zero();
  // ddth = VectorXd::Zero(info.dof.joint);

  for(int i=0; i<info.treeModelNum; i++){
    state[i].rB = Vector3d::Zero();
    state[i].RB = Matrix3d::Zero();
    state[i].voB = Vector3d::Zero();
    state[i].wB = Vector3d::Zero();
    state[i].th = VectorXd::Zero(info.treeModel[i].dof.joint);
    state[i].dth = VectorXd::Zero(info.treeModel[i].dof.joint);

    u[i] = VectorXd::Zero(info.treeModel[i].dof.all);

    for(int j=0; j<4; j++){
      k[i].vo[j] = k[i].w[j] = k[i].dvo[j] = k[i].dw[j] = Vector3d::Zero();
      k[i].dth[j] = k[i].ddth[j] = VectorXd::Zero(info.treeModel[i].dof.joint);
    }

    this->config.controlInput[i] = "no input";
  }
}
