/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::update(const Info &info, const double dt)
{
  if(debug) DEBUG;

  for(int i=0; i<info.treeModelNum; i++){
    Vector3d voBtemp = (k[i].vo[0] + 2*k[i].vo[1] + 2*k[i].vo[2] + k[i].vo[3])/6;
    Vector3d wBtemp = (k[i].w[0] + 2*k[i].w[1] + 2*k[i].w[2] + k[i].w[3])/6;

    se3exp(i, state[i].rB, state[i].RB, voBtemp, wBtemp, dt);
    state[i].th += dt*(k[i].dth[0] + 2*k[i].dth[1] + 2*k[i].dth[2] + k[i].dth[3])/6;

    state[i].voB += dt*(k[i].dvo[0] + 2*k[i].dvo[1] + 2*k[i].dvo[2] + k[i].dvo[3])/6;
    state[i].wB += dt*(k[i].dw[0] + 2*k[i].dw[1] + 2*k[i].dw[2] + k[i].dw[3])/6;
    state[i].dth += dt*(k[i].ddth[0] + 2*k[i].ddth[1] + 2*k[i].ddth[2] + k[i].ddth[3])/6;
  }
}
