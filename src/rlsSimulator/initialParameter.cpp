/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::initialParameter(const Config::Clock &clock, TreeModel &model)
{
  if(debug) DEBUG;

  t = clock.t0;

  // B部の初期位置
  rB = model.link[model.info.rootNode].r0;

  // B部の初期姿勢
  RB = model.link[model.info.rootNode].R0;

  // B部の初期空間速度
  voB = model.link[model.info.rootNode].vo0;

  // B部の初期角速度
  wB = model.link[model.info.rootNode].w0;

  // 関節の初期状態
  th = model.readJointStateVector("initial joint angle");
  dth = model.readJointStateVector("initial joint velocity");
}
