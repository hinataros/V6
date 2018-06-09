/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::cmp(Config &config, Info &info, TreeModel &hoap2)
{
  if(config.flag.debug) DEBUG;

  Vector3d f = Vector3d::Zero();

  for(int i=1; i<info.value.node; i++)
    f += cal_F.segment((6*(i-1)), 3);

  if(f(2) != 0.)
    // rcmp = rp - f.head(2)*hoap2.all.rC(2)/f(2);
    rcmp = rp + bb_Spx*dlCRef.head(2)/f(2);

  else
    rcmp = rp;
}
