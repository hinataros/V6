/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::integrator(Model &model, const int phase, const double dttemp)
{
  if(debug) DEBUG;

  se3exp(model.hoap2.link[model.hoap2.info.rootNode].r, model.hoap2.link[model.hoap2.info.rootNode].R, k.vo[phase], k.w[phase], dttemp);
  model.hoap2.writeJointStateVector("joint angle", th + dttemp*k.dth[phase]);

  model.hoap2.link[model.hoap2.info.rootNode].vo = voB + dttemp*k.dvo[phase];
  model.hoap2.link[model.hoap2.info.rootNode].w = wB + dttemp*k.dw[phase];
  model.hoap2.writeJointStateVector("joint velocity", dth + dttemp*k.ddth[phase]);
}
