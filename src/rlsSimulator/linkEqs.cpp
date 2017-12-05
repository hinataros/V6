#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::linkEqs(Config &config, Info &info, Model &model, Controller &controller, Output &output)
{
  if(config.flag.debug) DEBUG;

  model.hoap2.limb[0].node[0].r = rB;
  model.hoap2.limb[0].node[0].R = RB;
  model.hoap2.limb[0].node[0].vo = voB;
  model.hoap2.limb[0].node[0].w = wB;
  model.hoap2.all.th = th;
  model.hoap2.all.dth = dth;

  u = controller.controller(config, info, model, t);

  output.tm_temp = model.hoap2.tm_list;

  // smiyahara: 要検討
  if(config.controller.name=="rlsDynamics")
    output.dc_temp = controller.RlsDynamics::dc_list;

  output.pushBack(config, t);
}

void RLS::RlsSimulator::linkEqs(Config &config, Info &info, Model &model, Controller &controller)
{
  if(config.flag.debug) DEBUG;

  u = controller.controller(config, info, model, t);
}
