/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

int RLS::Output::setDat(ofstream& stream, string dataName, int i)
{
  if(dataName == "ext joint limit gradient"){
    stream << data.ext[i].jointLimitGradient.transpose();
    return 1;
  }

  else
    return -1; // error
}
