/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "controller.hpp"
#include "output.hpp"
#include "rlsSimulator.hpp"

void RLS::RlsSimulator::update(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  Vector3d voBtemp = (k.vo[0] + 2*k.vo[1] + 2*k.vo[2] + k.vo[3])/6;
  Vector3d wBtemp = (k.w[0] + 2*k.w[1] + 2*k.w[2] + k.w[3])/6;

  se3exp(config, rB, RB, voBtemp, wBtemp, info.sim.dt);
  th += info.sim.dt*(k.dth[0] + 2*k.dth[1] + 2*k.dth[2] + k.dth[3])/6;

  voB += info.sim.dt*(k.dvo[0] + 2*k.dvo[1] + 2*k.dvo[2] + k.dvo[3])/6;
  wB += info.sim.dt*(k.dw[0] + 2*k.dw[1] + 2*k.dw[2] + k.dw[3])/6;
  dth += info.sim.dt*(k.ddth[0] + 2*k.ddth[1] + 2*k.ddth[2] + k.ddth[3])/6;
}
