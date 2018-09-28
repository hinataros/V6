/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::updateState(const Model &model, const double &t)
{
  if(debug) DEBUG;

  state.rCpreDes = model.hoap2.all.rC - rC0;
  state.vCpreDes = model.hoap2.all.vC;

  state.rBpreDes = model.hoap2.link[model.hoap2.info.rootNode].r - rB0;
  state.vBpreDes = model.hoap2.link[model.hoap2.info.rootNode].v;
  state.xiBpreDes = R2xi(model.hoap2.link[model.hoap2.info.rootNode].R) - xiB0;
  state.dxiBpreDes = w2dxi(model.hoap2.link[model.hoap2.info.rootNode].w, R2xi(model.hoap2.link[model.hoap2.info.rootNode].R));

  state.rXpreDes = rX - rX0;
  // smiyahara: いつか変える
  state.drXpreDes = drXDes;

  state.cal_XpreDes = cal_X - cal_X0;
  state.cal_VpreDes = cal_V;

  // state.trev = t;
}

void RLS::RlsDynamics::updateSequence(const double &t, const int &num)
{
  if(debug) DEBUG;

  sequence[num].rCpreDes = sequence[num].rCf;

  sequence[num].rBpreDes = sequence[num].rBf;
  sequence[num].xiBpreDes = sequence[num].xiBf;

  sequence[num].rXpreDes = sequence[num].rXf;

  sequence[num].cal_XpreDes = sequence[num].cal_Xf;
  sequence[num].cal_XpreDesabs = sequence[num].cal_Xfabs;

  sequence[num].cal_FpreDes = sequence[num].cal_Ff;

  sequence[num].cal_FextpreDes = sequence[num].cal_Fextf;

  sequence[num].tw0 = t;
}
