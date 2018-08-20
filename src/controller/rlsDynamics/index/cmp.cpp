/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cmp(const TreeModel &model)
{
  if(debug) DEBUG;

  Vector3d f = Vector3d::Zero();

  for(int i=0; i<model.info.eeNum; i++)
    f += cal_F.segment((6*i), 3);

  if(f(2) != 0.)
    // rcmp = rp - f.head(2)*model.all.rC(2)/f(2);
    rcmp = rp + bb_Spx*dlCRef.head(2)/f(2);

  else
    rcmp = rp;
}
