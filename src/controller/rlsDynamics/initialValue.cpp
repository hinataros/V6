/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialValue(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  th0 = model.hoap2.all.th;

  rC0 = model.hoap2.all.rC;
  rB0 = model.hoap2.limb[0].node[0].r;
  xiB0 = R2xi(model.hoap2.limb[0].node[0].R);

  rX0 = model.hoap2.all.rC + sqrt(model.hoap2.all.rC(2)/abs(model.hoap2.ag(2)))*model.hoap2.all.vC;

  for(int i=1; i<info.value.node; i++)
    cal_X0.segment(6*(i-1),6) <<
      model.hoap2.limb[i].node[info.limb[i].dof].r,
      R2xi(model.hoap2.limb[i].node[info.limb[i].dof].R);

  cal_Fext0 <<
    model.hoap2.limb[0].node[0].f,
    model.hoap2.limb[0].node[0].n;

  // high gain control
  thDes = model.hoap2.all.th;

  readWork(config, info, "Default", 0);

  initialValueFlag = false;
}
