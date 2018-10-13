/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "rigidBodyModel.hpp"

void RLS::RigidBodyModel::initialize(const int &uniqueNum, RigidBodyModelInfo &info)
{
  if(debug) DEBUG;

  this->uniqueNum = uniqueNum;
}
