/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

#include <cstdlib>
#include <sys/stat.h>


void RLS::Output::dirCheck()
{
  if(debug) DEBUG;

  string ind = dir.gp.ind;
  const char *dir = ind.c_str();
  struct stat statBuf;

  string mkRsltTr = "mkrslt " + result.cmp + " -i " + result.ind;
  const char *command = mkRsltTr.c_str();

  if(stat(dir, &statBuf) != 0) {
    int ret = system(command);
    cout << "Generated composite directory: " << result.cmp << " individual directory: " << result.ind << endl;
  }

}
