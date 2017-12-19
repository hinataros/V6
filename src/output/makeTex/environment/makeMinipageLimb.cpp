#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::makeMinipageLimb(Config &config, Info &info, string category, string width, string name)
{
  if(config.flag.debug) DEBUG;

  string ref;
  string dir = config.controller.name + ":" + config.body.name+"/" + config.result.name.cmp+"/"+ "eps/" + config.result.name.ind+"/" + category+"/";

  for(int l=1; l<info.value.node; l++)
    ref +=
      "\\begin{minipage}{"+to_string(1./info.value.joint-.01)+"\\linewidth}\n"
      "\\centering\n"
      "\\includegraphics[width="+width+"\\hsize]{\\result/"+dir+name+"Limb"+to_string(l)+".eps}\n"
      "\\par\\footnotesize{}\n"
      "\\end{minipage}\n";

  return ref;
}
