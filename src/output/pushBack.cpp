/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::pushBack(const double &t)
{
  if(debug) DEBUG;

  data.t.push_back(t);
  data.tm.push_back(tm_temp);
  data.dc.push_back(dc_temp);
}
