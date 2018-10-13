/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "worldModel.hpp"

void RLS::WorldModel::initialize(const string &dir_share)
{
  if(debug) DEBUG;

  this->dir_share = dir_share;

  include.search = "relative";

  t0 = 0.;
  tf = 0.;
  dt = 0.;
  n = 0;
  ag = Vector3d::Zero();
}
