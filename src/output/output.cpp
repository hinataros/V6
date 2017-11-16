#include "config.hpp"
#include "info.hpp"
#include "output.hpp"

void RLS::Output::output(Config &config, Info &info)
{
  if(config.flag.debug) DEBUG;

  if(config.graph.tex)
    makeSimInfo(config);

  if(config.graph.flag){
    if(config.graph.gp)
      makeGpLibrary(config, info);

    makeModelDat(config, info);
    makeControllerDat(config, info);
    makeGraph(config);
  }

  if(config.cho.flag)
    makeMotionYaml(config, info);

  // if(config.gif.flag){
  //   makeGifDat(config, model);
  //   makeGif(config, model);
  // }
}
