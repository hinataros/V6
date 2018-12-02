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
}
