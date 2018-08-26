/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::torqueOutputConfig(const TreeModel::Info &info)
{
  if(debug) DEBUG;

  torqueOutputDesConfig(info);
  torqueOutputErrConfig(info);
  torqueOutputRefConfig(info);
  torqueOutputIndexConfig(info);
  torqueOutputIndexPrintConfig(info);
}
