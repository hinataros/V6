#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initialValue(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  rC0 = model.all.rC;
  rB0 = model.limb[0].node[0].r;
  xiB0 = R2xi(model.limb[0].node[0].R);

  for(int i=1; i<info.value.node; i++)
    cal_X0.segment(6*(i-1),6) <<
      model.limb[i].node[info.limb[i].dof].r,
      R2xi(model.limb[i].node[info.limb[i].dof].R);

  thDes = model.all.th;

  initialValueFlag = false;
}
