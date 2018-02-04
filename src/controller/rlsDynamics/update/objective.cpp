/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

int RLS::RlsDynamics::objective(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  if(!info.sim.state)
    return -1;

  MatrixXd Fz = MatrixXd::Identity(2*info.contact.num, 2*info.contact.num);
  MatrixXd S = MatrixXd::Zero(info.contact.num,info.contact.num);
  MatrixXd cal_S = MatrixXd::Zero(2*info.contact.num,6*info.contact.num);

  S <<
    0, -1,
    1, 0;

  for(int i=0; i<info.contact.num; i++){
    Fz.block(2*i,2*i,info.contact.num,info.contact.num) *= cal_F(6*i+2);
    cal_S.block(2*i,6*i+3,info.contact.num,info.contact.num) = S;
  }

  Pc = Fz.inverse()*cal_S;

  return 0;
}
