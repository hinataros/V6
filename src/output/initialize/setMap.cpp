/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::setMap()
{
  if(debug) DEBUG;

  // index
  map_use_function["dcm"] = &RLS::Output::dcm;
  map_use_function["sysMom"] = &RLS::Output::sysMom;
  map_use_function["localCop"] = &RLS::Output::localCop;
  map_use_function["netCop"] = &RLS::Output::netCop;
  map_use_function["stabilityIndex"] = &RLS::Output::stabilityIndex;

  // walking
  map_use_function["vrpDes4walking"] = &RLS::Output::vrpDes4walking;
  map_use_function["stabilityIndex4walking"] = &RLS::Output::stabilityIndex4walking;
  map_use_function["stabilityIndex4walkingDes"] = &RLS::Output::stabilityIndex4walkingDes;

  // joint value
  map_use_function["joint"] = &RLS::Output::joint;
  map_use_function["joint with torso"] = &RLS::Output::joint_wTorso;
  map_use_function["joint with torso 1"] = &RLS::Output::joint_wTorso1;
  map_use_function["joint with torso 3"] = &RLS::Output::joint_wTorso3;
  
  // ext
  map_use_function["joint limit gradient"] = &RLS::Output::jointLimitGradient;
  map_use_function["joint limit gradient with torso 1"] = &RLS::Output::jointLimitGradient_wTorso1;
  map_use_function["joint limit gradient with torso 3"] = &RLS::Output::jointLimitGradient_wTorso3;

}
