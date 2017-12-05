#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::initialParameter(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  t = info.sim.t0;

  // B部の初期位置
  rB = model.hoap2.limb[0].node[0].r0;

  // B部の初期姿勢
  RB = xi2R(model.hoap2.limb[0].node[0].xi0);

  // B部の初期速度
  voB = model.hoap2.limb[0].node[0].vo =
    model.hoap2.limb[0].node[0].v0 + cross(model.hoap2.limb[0].node[0].r0) * model.hoap2.limb[0].node[0].w0;
  wB = model.hoap2.limb[0].node[0].w0;

  // 関節の初期状態
  for(int i=1, temp=0; i<info.value.node; i++){
    for(int j=0; j<info.limb[i].dof; j++){
      th(temp+j) = model.hoap2.limb[i].node[j].th0;
      dth(temp+j) = model.hoap2.limb[i].node[j].dth0;
    }

    temp += info.limb[i].dof;
  }

  // rB0=0としたとき慣性座標を足とする
  if(config.model.name=="skeleton"||config.model.name=="skeletonA7"){
    model.hoap2.limb[0].node[0].r = rB;
    model.hoap2.limb[0].node[0].R = RB;
    model.hoap2.limb[0].node[0].vo = voB;
    model.hoap2.limb[0].node[0].w = wB;
    model.hoap2.all.th = th;
    model.hoap2.all.dth = dth;

    model.hoap2.update(config, info);
    rB(2) = -model.hoap2.limb[1].node[info.limb[1].dof].r(2);
  }
}
