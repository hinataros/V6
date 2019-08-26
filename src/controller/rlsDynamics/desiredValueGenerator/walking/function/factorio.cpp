/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "walkingFunction.hpp"


double RLS::WalkingFunction::factorio(int num, int step)
{
  if(!num){
    return 1;
  }

  int ret = 1;
  int n = num;

  for(int i=0; i<step; i++)
    ret *= (n-i);

  return (double)ret;
}
