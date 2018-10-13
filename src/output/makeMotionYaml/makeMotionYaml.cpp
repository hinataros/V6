/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::makeMotionYaml()
{
  if(debug) DEBUG;

  for(int i=0; i<info->treeModelNum; i++)
    makeTreeModelMotionYaml(i);
}
