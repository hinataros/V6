/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::linkEqs(Config &config, Model &model, RlsDynamics &rlsDynamics, Output &output)
{
  if(debug) DEBUG;

  model.hoap2.link[model.hoap2.info.rootNode].r = rB;
  model.hoap2.link[model.hoap2.info.rootNode].R = RB;
  model.hoap2.link[model.hoap2.info.rootNode].vo = voB;
  model.hoap2.link[model.hoap2.info.rootNode].w = wB;
  model.hoap2.writeJointStateVector("joint angle", th);
  model.hoap2.writeJointStateVector("joint velocity", dth);

  u = rlsDynamics.rlsDynamics(config, model, t);

  output.tm_temp = model.hoap2.tm_list;
  output.dc_temp = rlsDynamics.dc_list;

  // output.pushBack(config, t);
}

void RLS::RlsSimulator::linkEqs(Config &config, Model &model, RlsDynamics &rlsDynamics)
{
  if(debug) DEBUG;

  u = rlsDynamics.rlsDynamics(config, model, t);
}
