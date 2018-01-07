/**
   @author Sho Miyahara 2017
*/

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
  RB = model.hoap2.limb[0].node[0].R0;

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
}
