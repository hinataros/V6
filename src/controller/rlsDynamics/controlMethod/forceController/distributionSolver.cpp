/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "info.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::distributionSolver(Config &config, Info &info, Model &model)
{
  if(config.flag.debug) DEBUG;

  MatrixXd G = MatrixXd::Identity(c, c);
  VectorXd g = VectorXd::Zero(c);

  MatrixXd CE = cal_Pc;
  VectorXd ce = cal_dLBRef + cal_GB;

  QuadProgpp::solver(G, g, "e", CE, ce, cal_FcBarRef);
}
