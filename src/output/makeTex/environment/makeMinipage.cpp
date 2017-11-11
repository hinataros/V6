#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

string RLS::Output::makeMinipage(Config &config, string category, string width, string name)
{
  if(config.flag.debug) DEBUG;

  string ref =
    "\\begin{minipage}{0.24\\linewidth}\n"
    "\\centering\n"
    "\\includegraphics[width="+width+"\\hsize]{\\data/eps/"+config.controller.name +":"+config.model.name+"/"+config.name+"/"+category+"/"+name+".eps}\n"
    "\\par\\footnotesize{}\n"
    "\\end{minipage}\n";

  return ref;
}
