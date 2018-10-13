/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::setModel(const WorldModel &worldModel, Info &info, const int &controllerNum)
{
  if(debug) DEBUG;

  this->worldModel = &worldModel;

  this->info = &info;

  this->controllerNum = controllerNum;
}
