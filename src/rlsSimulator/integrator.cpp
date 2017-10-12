#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::integrator(Config &config, Model &model, int phase, double dttemp)
{
  if(config.flag.debug) DEBUG;

  se3exp(config, model.limb[0].node[0].r, model.limb[0].node[0].R, k.vo[phase], k.w[phase], dttemp);
  model.all.th = th + dttemp*k.dth[phase];

  model.limb[0].node[0].vo = voB + dttemp*k.dvo[phase];
  model.limb[0].node[0].w = wB + dttemp*k.dw[phase];
  model.all.dth = dth + dttemp*k.ddth[phase];
}
