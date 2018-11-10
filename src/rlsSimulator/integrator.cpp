/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::integrator(const int phase, const double dttemp, Model &model)
{
  if(debug) DEBUG;

  for(int i=0; i<model.info.treeModelNum; i++){
    se3exp(i, model.treeModel[i].link[model.info.treeModel[i].rootNode].r, model.treeModel[i].link[model.info.treeModel[i].rootNode].R, k[i].vo[phase], k[i].w[phase], dttemp);
    model.treeModel[i].writeJointState("joint angle", state[i].th + dttemp*k[i].dth[phase]);

    model.treeModel[i].link[model.info.treeModel[i].rootNode].vo = state[i].voB + dttemp*k[i].dvo[phase];
    model.treeModel[i].link[model.info.treeModel[i].rootNode].w = state[i].wB + dttemp*k[i].dw[phase];
    model.treeModel[i].writeJointState("joint velocity", state[i].dth + dttemp*k[i].ddth[phase]);
  }
}
