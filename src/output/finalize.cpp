/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::finalize()
{
  if(debug) DEBUG;

  vector<double>().swap(data.t);
  vector<TreeModelList>().swap(data.tm);
  vector<RlsDynamicsList>().swap(data.dc);
}
