/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::diffEqs(const int phase, Model &model)
{
  if(debug) DEBUG;

  for(int i=0; i<model.info.treeModelNum; i++){
    Vector3d rB = model.treeModel[i].link[model.info.treeModel[i].rootNode].r;

    if(this->config.controlInput[i]=="velocity"){
      k[i].vo[phase] = u[i].head(3) - cross(u[i].segment(3,3))*rB;
      k[i].w[phase] = u[i].segment(3,3);
      k[i].dth[phase] = u[i].tail(model.info.treeModel[i].dof.joint);

      k[i].dvo[phase] = Vector3d::Zero();
      k[i].dw[phase] = Vector3d::Zero();
      k[i].ddth[phase] = VectorXd::Zero(model.info.treeModel[i].dof.joint);

    }else{
      Vector3d vB = model.treeModel[i].link[model.info.treeModel[i].rootNode].v;
      Vector3d wB = model.treeModel[i].link[model.info.treeModel[i].rootNode].w;

      if(this->config.controlInput[i]=="acceleration"){
        dvoB = u[i].head(3) - (cross(u[i].segment(3,3))*rB + cross(wB)*vB);
        dwB = u[i].segment(3,3);
        ddth = u[i].tail(model.info.treeModel[i].dof.joint);
      }
      // if(this->config.controlInput=="torque"){
      // lmp(config, model, u, controller.cal_Jc, controller.cal_dJc, controller.Bc);
      // forwardDynamics(config, model, u);

      // VectorXd ddq;
      // ddq = model.hoap2.all.M.inverse()*( -model.hoap2.all.c - model.hoap2.all.g);

      // dvoB = ddq.head(3) - (cross(ddq.segment(3,3))*model.hoap2.limb[0].node[0].r + cross(model.hoap2.limb[0].node[0].w)*model.hoap2.limb[0].node[0].v);
      // dwB = ddq.segment(3,3);
      // ddth = ddq.tail(info.dof.joint);
      // }
      else{
        dvoB = Vector3d::Zero();
        dwB = Vector3d::Zero();
        ddth = VectorXd::Zero(model.info.treeModel[i].dof.joint);
      }

      k[i].vo[phase] = model.treeModel[i].link[model.info.treeModel[i].rootNode].vo;
      k[i].w[phase] = wB;
      k[i].dth[phase] = model.treeModel[i].readJointState("joint velocity");

      k[i].dvo[phase] = dvoB;
      k[i].dw[phase] = dwB;
      k[i].ddth[phase] = ddth;
    }
  }
}
