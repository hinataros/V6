/**
   @author Sho Miyahara 2018
*/

#include <fstream>

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

int RLS::Output::setDat(ofstream& stream, string dataName, int i)
{
  if(dataName=="hogeDes")
    stream << data.ext[i].hogeDes.transpose();
  // else if(dataName=="dhogeDes")
  //   stream << data.ext[i].dhogeDes.transpose();
  else
    return 0;

  return 1;
}
