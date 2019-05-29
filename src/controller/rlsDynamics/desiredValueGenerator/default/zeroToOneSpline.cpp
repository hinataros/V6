/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::zeroToOneSpline(const int &controlNum, const double &t)
{
  if(debug) DEBUG;

  double t0 = tw0[controlNum];
  double tf = twf[controlNum];

  zeroToOne = makeSpline5(t-t0, tf, 0., 1.);
}
