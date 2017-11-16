#include "config.hpp"

void RLS::Config::setDir()
{
  if(flag.debug) DEBUG;

  dir.result = dir.link + "result/";
  dir.set = dir.result + controller.name + ":" + model.name + "/";
  dir.data.main = dir.set + data.name.main + "/";

  dir.dat.main = dir.data.main + "dat/";
  dir.eps.main = dir.data.main + "eps/";
  dir.gp.main = dir.data.main + "gp/";
  dir.pdf.main = dir.data.main + "pdf/";

  dir.dat.sub = dir.dat.main + data.name.sub + "/";
  dir.eps.sub = dir.eps.main + data.name.sub + "/";
  dir.gp.sub = dir.gp.main + data.name.sub + "/";
  dir.pdf.sub = dir.pdf.main + "src/" + data.name.sub + "/";

  dir.interface = dir.result + "interface/";
}
