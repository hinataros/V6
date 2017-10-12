#include "config.hpp"
#include "info.hpp"
#include "treeModel.hpp"

void RLS::TreeModel::update(Config &config, Info &info)
{
  if (config.flag.debug) DEBUG;

  position(config, info, limb[0].node[0].r, limb[0].node[0].R, all.th);
  velocity(config, info, limb[0].node[0].vo, limb[0].node[0].w, all.dth);
  jacobian(config, info);
  diffJacobian(config, info);

  if(config.controller.dynamics){
    identityVectorMethod(config, info);
    analyticalDynamics(config, info);
  }

  outputConfig(config, info);
}
