/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "walking.hpp"

void RLS::Walking::setStartTime(const double &tw0)
{
  this->tw0 = tw0;
}

void RLS::Walking::setFinishTime(const double &twf)
{
  this->twf = twf;
}

void RLS::Walking::setInitialTime(const double &tInitial)
{
  this->tInitial = tInitial;
}

void RLS::Walking::setStartValue(const Vector3d &rXpreDes)
{
  this->rXpreDes = rXpreDes;
}

void RLS::Walking::setFinishValue(const Vector3d &rXf)
{
  this->rXf = rXf;
}
