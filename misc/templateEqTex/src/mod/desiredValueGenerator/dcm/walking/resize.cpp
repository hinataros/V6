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

  g = 9.81;

  wX = 0.;

  des = Vector3d::Zero();

  rX0 = Vector3d::Zero();
  rCw0 = Vector3d::Zero();

  // rxw0 = VectorXd::Zero(6*4); // amiyata

  tw0 = 0.;
  twf = 0.;
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
  ht_config.zOsc = 0.;

  ht_config.tstab = 0.;

  vwpNum = 0;
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
}
