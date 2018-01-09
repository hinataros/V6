/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::baseAngularMomentum(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  dlBRef =
    - model.hoap2.all.m*cross(rB2C).transpose()*dvCRef + IC*dwBRef
    - model.hoap2.all.m*cross(drB2C).transpose()*cal_VM.head(3) + dIC*cal_VM.tail(3);
}
