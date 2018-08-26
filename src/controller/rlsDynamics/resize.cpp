/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::resize(Model &model)
{
  if(debug) DEBUG;

  th = model.hoap2.readJointStateVector("joint angle");
  dth = model.hoap2.readJointStateVector("joint velocity");

  cal_X = model.hoap2.readEndEffectorValueVector("6D position");
  cal_V = model.hoap2.readEndEffectorValueVector("spatial velocity");
  cal_F = model.hoap2.readEndEffectorValueVector("wrench");
}
