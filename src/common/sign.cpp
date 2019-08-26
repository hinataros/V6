#include "config.hpp"
#include "common.hpp"


double RLS::Common::sign(double A)
{
  if(debug) DEBUG;

  return (double)(A>0)-(A<0);
}
