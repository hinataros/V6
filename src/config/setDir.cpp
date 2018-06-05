/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"

void RLS::Config::setDir()
{
  if(flag.debug) DEBUG;

  dir.share = dir.link + "share/";
  dir.cnoid = dir.share + "project/" + cnoid.name + ".cnoid";
  dir.body = dir.share + "model/";
  dir.model = dir.link + "yaml/model/" + body.name+".model";
  dir.work = dir.link + "yaml/work/" + controller.name+"/" + controller.work+".work";

  dir.result = dir.link + "result/";
  dir.cmp = dir.result + result.name.cmp+"/";

  dir.dat.cmp = dir.cmp + "dat/";
  dir.eps.cmp = dir.cmp + "eps/";
  dir.gp.cmp = dir.cmp + "gp/";
  dir.pdf.cmp = dir.cmp + "pdf/";

  dir.dat.ind = dir.dat.cmp + result.name.ind+"/";
  dir.eps.ind = dir.eps.cmp + result.name.ind+"/";
  dir.gp.ind = dir.gp.cmp + result.name.ind+"/";
  dir.pdf.ind = dir.pdf.cmp + "src/" + result.name.ind+"/";

  dir.interface = dir.result + "interface/";
}
