/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "common.hpp"


bool RLS::Common::nanCheck(VectorXd vec){
  for(int i=0;i<vec.rows();i++)
    if(isnan(vec(i)))
      return false;
  return true;
}
