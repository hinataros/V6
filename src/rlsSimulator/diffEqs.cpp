/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::diffEqs(Config &config, Model &model, const int phase)
{
  if(debug) DEBUG;

  if(config.controller.input=="velocity"){
    k.vo[phase] = u.head(3) - cross(u.segment(3,3))*model.hoap2.link[model.hoap2.info.rootNode].r;
    k.w[phase] = u.segment(3,3);
    k.dth[phase] = u.tail(model.hoap2.info.dof.joint);

    k.dvo[phase] = Vector3d::Zero();
    k.dw[phase] = Vector3d::Zero();
    k.ddth[phase] = VectorXd::Zero(model.hoap2.info.dof.joint);

  }else{
    if(config.controller.input=="acceleration"){
      dvoB = u.head(3) - (cross(u.segment(3,3))*model.hoap2.link[model.hoap2.info.rootNode].r + cross(model.hoap2.link[model.hoap2.info.rootNode].w)*model.hoap2.link[model.hoap2.info.rootNode].v);
      dwB = u.segment(3,3);
      ddth = u.tail(model.hoap2.info.dof.joint);
    }
    // if(config.controller.input=="torque"){
      // lmp(config, model, u, controller.cal_Jc, controller.cal_dJc, controller.Bc);
      // forwardDynamics(config, model, u);

      // VectorXd ddq;
      // ddq = model.hoap2.all.M.inverse()*( -model.hoap2.all.c - model.hoap2.all.g);

      // dvoB = ddq.head(3) - (cross(ddq.segment(3,3))*model.hoap2.limb[0].node[0].r + cross(model.hoap2.limb[0].node[0].w)*model.hoap2.limb[0].node[0].v);
      // dwB = ddq.segment(3,3);
      // ddth = ddq.tail(info.dof.joint);
    // }

    k.vo[phase] = model.hoap2.link[model.hoap2.info.rootNode].vo;
    k.w[phase] = model.hoap2.link[model.hoap2.info.rootNode].w;
    k.dth[phase] = model.hoap2.readJointStateVector("joint velocity");

    k.dvo[phase] = dvoB;
    k.dw[phase] = dwB;
    k.ddth[phase] = ddth;
  }
}
