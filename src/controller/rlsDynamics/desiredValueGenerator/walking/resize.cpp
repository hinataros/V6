/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::resize()
{
  if(debug) DEBUG;

  rXDes = Vector3d::Zero();
  drXDes = Vector3d::Zero();
  rXBarDes = Vector3d::Zero();
  drXBarDes = Vector3d::Zero();

  // amiyata
  rCDes = Vector3d::Zero();
  drCDes = Vector3d::Zero();
  ddrCDes = Vector3d::Zero();

  g = 9.81;

  wX = 0.;

  des = Vector3d::Zero();

  rX0 = Vector3d::Zero();
  rCw0 = Vector3d::Zero();

  tw0 = 0.;
  twf = 0.;
  tInitial = 0.; // amiyata
  rXpreDes = Vector3d::Zero();
  rXf = Vector3d::Zero();
  rXfabs = Vector3d::Zero();

  ht_config.convergenceNum = 0;
  ht_config.dtstep = 0.;
  ht_config.dtDSstep = 0.;
  ht_config.alphaDSstep = 0.;
  ht_config.alphaHTstep = 0.;
  ht_config.offset = 0.;
  ht_config.toe = 0.;
  ht_config.heel = 0.;
  // amiyata
  ht_config.zOsc = 0.;
  ht_config.ipDim = 2;

  ht_config.tstab = 0.;

  vwpNum = 0;
  vwp.clear(); // amiyata
  vwp.shrink_to_fit();
  convergencePhaseNum = 1;

  phaseDS = 0;
  flagDS = true;

  stepPhase = 0;
  tstep0 = 0.;
  tstep = 0.;
  tDS0 = 0.;

  // polynomial
  initial_walking = true;
  tphasef = 0.;
  support = 0;

  // ext HT
  rext = Vector3d::Zero();

  // amiyata
  convT = 0.;
  ToptimF = false;
  oscF = false;
}