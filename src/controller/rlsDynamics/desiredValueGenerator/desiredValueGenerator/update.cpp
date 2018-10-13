/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::update(const double &t)
{
  state.rCpreDes = model->rC - rC0;
  state.vCpreDes = model->vC;

  state.rBpreDes = model->rB - rB0;
  state.vBpreDes = model->vB;
  state.xiBpreDes = R2xi(model->RB) - xiB0;
  state.dxiBpreDes = w2dxi(model->wB, R2xi(model->RB));

  state.rXpreDes = model->rX - rX0;
  // smiyahara: いつか変える
  state.drXpreDes = drXDes;

  state.cal_XpreDes = model->cal_X - cal_X0;
  state.cal_VpreDes = model->cal_V;
}

void RLS::DesiredValueGenerator::update(const double &t, const int &num)
{
  if(debug) DEBUG;

  sequence[num].rCpreDes = sequence[num].rCf;

  sequence[num].rBpreDes = sequence[num].rBf;
  sequence[num].xiBpreDes = sequence[num].xiBf;

  sequence[num].rXpreDes = sequence[num].rXf;

  sequence[num].cal_XpreDes = sequence[num].cal_Xf;
  sequence[num].cal_XpreDesabs = model->cal_X;

  sequence[num].cal_FpreDes = sequence[num].cal_Ff;

  sequence[num].cal_FextpreDes = sequence[num].cal_Fextf;

  sequence[num].tw0 = t;
}
