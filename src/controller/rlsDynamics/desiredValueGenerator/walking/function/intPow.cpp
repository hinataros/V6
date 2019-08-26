
#include "config.hpp"
#include "walkingFunction.hpp"


double RLS::WalkingFunction::intPow(double pow, int n)
{
  double ret=1.;
  for(int i=0; i<n; i++)
    ret *= pow;

  return ret;
}
