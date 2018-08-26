/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::basis()
{
  if(debug) DEBUG;

  Bc = bb_Rk*Bc_k;
  Bm = bb_Rk*Bm_k;

  // diff
  dBc = bb_dRk*Bc_k;
  dBm = bb_dRk*Bm_k;
}
