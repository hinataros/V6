#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::diffEqs(Config &config, Info &info, Model &model, int phase)
{
  if(config.flag.debug) DEBUG;

  if(config.controller.input=="velocity"){
    k.vo[phase] = u.head(3) - cross(u.segment(3,3))*model.limb[0].node[0].r;
    k.w[phase] = u.segment(3,3);
    k.dth[phase] = u.tail(info.dof.joint);

    k.dvo[phase] = Vector3d::Zero();
    k.dw[phase] = Vector3d::Zero();
    k.ddth[phase] = VectorXd::Zero(info.dof.joint);

  }else{
    if(config.controller.input=="acceleration"){
      dvoB = u.head(3) - (cross(u.segment(3,3))*model.limb[0].node[0].r + cross(model.limb[0].node[0].w)*model.limb[0].node[0].v);
      dwB = u.segment(3,3);
      ddth = u.tail(info.dof.joint);

    }
    if(config.controller.input=="torque"){
      // lmp(config, model, u, controller.cal_Jc, controller.cal_dJc, controller.Bc);
      // forwardDynamics(config, model, u);

      // VectorXd ddq;
      // ddq = model.all.M.inverse()*( -model.all.c - model.all.g);

      // dvoB = ddq.head(3) - (cross(ddq.segment(3,3))*model.limb[0].node[0].r + cross(model.limb[0].node[0].w)*model.limb[0].node[0].v);
      // dwB = ddq.segment(3,3);
      // ddth = ddq.tail(info.dof.joint);
    }

    k.vo[phase] = model.limb[0].node[0].vo;
    k.w[phase] = model.limb[0].node[0].w;
    k.dth[phase] = model.all.dth;

    k.dvo[phase] = dvoB;
    k.dw[phase] = dwB;
    k.ddth[phase] = ddth;
  }
}
