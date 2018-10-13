/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "output.hpp"

void RLS::Output::setDir(const string &dir_link)
{
  if(debug) DEBUG;

  dir.result = dir_link + "result/";
  dir.motion = dir_link + "share/motion/";

  dir.interface = dir.result + "interface/";

  dir.cmp = dir.result + result.cmp+"/";

  dir.dat.cmp = dir.cmp + "dat/";
  dir.gp.cmp = dir.cmp + "gp/";
  dir.eps.cmp = dir.cmp + "eps/";
  dir.pdf.cmp = dir.cmp + "pdf/";
  dir.gif.cmp = dir.cmp + "gif/";

  dir.dat.ind = dir.dat.cmp + result.ind+"/";
  dir.gp.ind = dir.gp.cmp + result.ind+"/";
  dir.eps.ind = dir.eps.cmp + result.ind+"/";
  dir.gif.ind = dir.gif.cmp + result.ind+"/";
  dir.pdf.ind = dir.pdf.cmp + "src/" + result.ind+"/";
}
